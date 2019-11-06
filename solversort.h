// Copyright 2019 SD_Homework_Team

#ifndef SOLVER_H_
#define SOLVER_H_

#include <fstream>
#include <string>
#include <utility>
#include <list>
#include <vector>
#include "Graph.h"
#include "hashString.h"
#include "Driver.h"
#include <iomanip>
#define INF 1000000000
#ifndef H_SIZE
#define H_SIZE 666013
#endif // H_SIZE
#include <algorithm>

class solver {
	public:
		Graph<std::string> graph;
		Hash<std::string, int> h;
		std::vector<Driver> drivers;

		solver() {
			graph = Graph<std::string>(&hashString);
			h = Hash<std::string, int>(H_SIZE, &hashString);
		}

		// citeste si creeaza graful
		void readGraph(std::ifstream& fin) {
			int n, m;
			fin >> n >> m;

			// adauga noduri in graf
			for (int i = 1; i <= n; ++i) {
				std::string s;
				fin >> s;
				graph.addNode(s);
			}

			// adauga muchii in graf
			for (int i = 1; i <= m; ++i) {
				std::string s1, s2;
				fin >> s1 >> s2;
				graph.addEdge(s1, s2);
			}
		}

		void task1_solver(std::ifstream& fin, std::ofstream& fout) {
			readGraph(fin);
			int q1;
			fin >> q1;

			for (int i = 1; i <= q1; ++i) {
				std::string s1, s2;
				fin >> s1 >> s2;

				// daca distanta este -1 inseamna ca nu exista drum s1-s2
				if (graph.getDist(s1, s2) == -1) {
					fout << "n" << std::endl;
				} else {
					fout << "y" << std::endl;
				}
			}
		}

		void task2_solver(std::ifstream& fin, std::ofstream& fout) {
			int q2;
			fin >> q2;

			for (int i = 1; i <= q2; ++i) {
				std::string s1, s2;
				fin >> s1 >> s2;

				// se afiseaza distanta de la s1 la s2
				fout << graph.getDist(s1, s2) << std::endl;
			}
		}

		void task3_solver(std::ifstream& fin, std::ofstream& fout) {
			int q3;
			fin >> q3;

			for (int i = 1; i <= q3; ++i) {
				char c;
				std::string junction1, junction2;
				int nr;

				fin >> c >> junction1 >> junction2 >> nr;

				if (c == 'c') {
					switch (nr) {
						case 0:
							// se adauga muchia junction1-junction2
							graph.addEdge(junction1, junction2);
							break;
						case 1:
							// se sterge muchia dintre junction1 si junction2
							graph.removeEdge(junction1, junction2);
							graph.removeEdge(junction2, junction1);
							break;
						case 2:
							// se face muchia junction1-junction2 bidirectionala
							graph.addEdge(junction1, junction2);
							graph.addEdge(junction2, junction1);
							break;
						case 3:
							// se schimba sensul muchiei junction1-junction2
							graph.reverseEdge(junction1, junction2);
							break;
					}
				} else {
					switch (nr) {
						case 0:
							// se verifica daca exista drum junction1-junction2
							if (graph.getDist(junction1, junction2) == -1) {
								fout << "n" << std::endl;
							} else {
								fout << "y" << std::endl;
							} 
							break;
						case 1:
							// se afiseaza distanta junction1-junction2
							fout << graph.getDist(junction1, junction2)
								 << std::endl;
							break;
						case 2:
							std::string junction3;
							fin >> junction3;
							
							int length1 = graph.getDist(junction1, junction3);
							int length2 = graph.getDist(junction3, junction2);

							// se afisiaza distanta j1-j2 trecand prin j3
							if (length1 == -1 || length2 == -1) {
								fout << "-1" << std::endl;
							} else {
								fout << length1 + length2 << std::endl;
							}
							break;
					}
				}
			}
		}

		static bool cmpRating(Driver a, Driver b) {
			if (a.ratingAvg == b.rating) {
				return a.name < b.name;
			}
			return a.ratingAvg > b.ratingAvg;
		}

		static bool cmpRides(Driver a, Driver b) {
			if (a.rides == b.rides) {
				return a.name < b.name;
			}
			return a.rides > b.rides;
		}

		static bool cmpDist(Driver a, Driver b) {
			if (a.dist == b.dist) {
				return a.name < b.name;
			}
			return a.dist > b.dist;
		}

		void task4_solver(std::ifstream& fin, std::ofstream& fout) {
			std::vector<std::vector<int>> mDist = graph.getMDist();
			int q4, nrDrivers = 0;
			fin >> q4;

			for (int i = 1; i <= q4; i++) {
				char c;
				fin >> c;

				switch(c) {
					case 'd': {
						std::string name, junction;
						fin >> name >> junction;

						if (h.hasKey(name) == false) {
							// se adauga un sofer nou
							h.addPair(name, nrDrivers);
							drivers.push_back(Driver(name, junction));

							nrDrivers++;
						} else {
							// devine online un sofer vechi
							int index = h[name];
							drivers[index].status = true;
							drivers[index].junction = junction;
						}
						break;
					}
					case 'b': {
						std::string name;
						fin >> name;

						// un sofer devine offline
						drivers[h[name]].status = false;
						break;
					}
					case 'r': {
						std::string start, end;
						fin >> start >> end;

						int rating;
						fin >> rating;

						int nodeStart = graph.getNodeIndex(start);
						int nodeEnd = graph.getNodeIndex(end);

						int index = -1;
						int mini = INF;

						 // se cauta cel mai apropiat sofer online de start
							for (int i = 0; i < nrDrivers; i++) {
								if (drivers[i].status == true) {
									int node = graph.getNodeIndex(
												drivers[i].junction);

									if (mDist[node][nodeStart] != -1) {
									 	if (mini > mDist[node][nodeStart] ||
									 		(mini == mDist[node][nodeStart] &&
									 		drivers[i] < drivers[index])) {
											index = i;
											mini =  mDist[node][nodeStart];
										}
									}
							}
						}

						if (index == -1) {
							fout << "Soferi indisponibili" << std::endl;
							break;
						}

						// daca se gaseste un sofer i se actualizeaza datele
						// daca exista un drum start-end aceste se efectueaza
						if (mDist[nodeStart][nodeEnd] != -1) {
							drivers[index].dist += mini
												+ mDist[nodeStart][nodeEnd];
							drivers[index].rides++;
							drivers[index].rating += rating;
							drivers[index].ratingAvg = 1.0 *
													   drivers[index].rating /
													   drivers[index].rides;
							drivers[index].junction = end;
						} else {
							/* daca nu exista un drum start-end se cauta o
							destinatie vecina lui end */
							std::list<int> neighbours;
							neighbours = graph.getNodeNeighbours(end); 

							int neighbour = -1;
							int mini2 = INF;

							for (auto it = neighbours.begin();
								it != neighbours.end(); it++) {
								if (mDist[nodeStart][*it] != -1) {
									if (mDist[nodeStart][*it] < mini2) {
										mini2 = mDist[nodeStart][*it];
										neighbour = *it;
									}
								}
							}

							/* daca se gaseste o destinatie vecina lui end
							se efectueaza cursa */
							if (neighbour != -1) {
								drivers[index].dist += mini + mini2;
								drivers[index].rides++;
								drivers[index].rating += rating;
								drivers[index].ratingAvg = 1.0 *
														 drivers[index].rating
														 / drivers[index].rides;
								drivers[index].junction =
								graph.getNodeData(neighbour);
							} else {
								fout << "Destinatie inaccesibila" << std::endl;
							}
						}
						break;
					}
					case 'i': {
						std::string name, restString;
						fin >> restString >> name;
						int index = h[name];

						// se afiseaza datele soferului name
						fout << name << ": " << drivers[index].junction << " "
							 << std::fixed << std::setprecision(3)
							 << drivers[index].ratingAvg << " "
							 << drivers[index].rides << " "
							 << drivers[index].dist << " ";

						if (drivers[index].status == true) {
							fout << "online" << std::endl;
						} else {
							fout << "offline" << std::endl;
						}
						break;
					}
					case 't': {
						/* pentru fiecare top se realizeaza o sortare si se aleg
						primii nr soferi */
						std::string top;
						fin >> top;

						int nr;
						fin >> nr;

						nr = std::min(nr, nrDrivers);
						if (top == std::string("op_rating")) {
							std::vector<Driver> copy = drivers;
							/*for (int i = 0; i < nrDrivers; i++) {
								for (int j = i + 1; j < nrDrivers; j++) {
									if (copy[i].ratingAvg < copy[j].ratingAvg ||
										(copy[i].ratingAvg == copy[j].ratingAvg 
										&& copy[i].name > copy[j].name)) {
										Driver aux = copy[i];
										copy[i] = copy[j];
										copy[j] = aux;
									}
								}
							}*/
							std::sort(copy.begin(), copy.end(), cmpRating);
							for (int i = 0; i < nr; i++) {
								fout << copy[i].name << ":" << std::fixed
									<< std::setprecision(3) << copy[i].ratingAvg
									<< " ";
							}

							fout << std::endl;
						} else if (top == std::string("op_dist")) {
								std::vector<Driver> copy = drivers;
								// for (int i = 0; i < nrDrivers; i++) {
								// 	for (int j = i + 1; j < nrDrivers; j++) {
								// 		if (copy[i].dist < copy[j].dist ||
								// 			(copy[i].dist == copy[j].dist &&
								// 			copy[i].name > copy[j].name)) {
								// 			Driver aux = copy[i];
								// 			copy[i] = copy[j];
								// 			copy[j] = aux;
								// 		}
								// 	}
								// }
								std::sort(copy.begin(), copy.end(), cmpDist);
								for (int i = 0; i < nr; i++) {
									fout << copy[i].name << ":" << copy[i].dist 
										<< " ";
								}

								fout << std::endl;
						} else if (top == std::string("op_rides")) {
								std::vector<Driver> copy = drivers;
								// for (int i = 0; i < nrDrivers; i++) {
								// 	for (int j = i + 1; j < nrDrivers; j++) {
								// 		if (copy[i].rides < copy[j].rides ||
								// 			(copy[i].rides == copy[j].rides &&
								// 			copy[i].name > copy[j].name)) {
								// 			Driver aux = copy[i];
								// 			copy[i] = copy[j];
								// 			copy[j] = aux;
								// 		}
								// 	}
								// }
								std::sort(copy.begin(), copy.end(), cmpRides);
								for (int i = 0; i < nr; i++) {
									fout << copy[i].name << ":" << copy[i].rides 
										<< " ";
								}
								fout << std::endl;
						}
						break;
					}
				}
			}
		}

		void task5_solver(std::ifstream& fin, std::ofstream& fout) {
			int fuel;
			std::string name;

			fin >> fuel >> name;

			int nr;
			fin >> nr;

			// se introduc destinatiile posibile intr-un vector
			std::vector<std::string> des;
			for (int i = 0; i < nr; i++) {
				std::string s;
				fin >> s;
				des.push_back(s);
			}

			std::vector<int> dist(graph.nrNodes, -1);
			std::vector<std::string> disp = graph.displayAllNeighbours(
									drivers[h[name]].junction, fuel, des, dist);

			// se sorteaza in functie de nume cand distantele sunt egale
			int l = disp.size();
			for (int i = 0; i < l; i++) {
				for (int j = i + 1; j < l; j++) {
					if (dist[graph.getNodeIndex(disp[i])] ==
						dist[graph.getNodeIndex(disp[j])] &&
						disp[i] > disp[j]) {
						std::swap(disp[i], disp[j]);
					}
				}
			}

			for (auto it = disp.begin(); it != disp.end(); ++it) {
				fout << *it << " ";
			}
		}
};

#endif  // SOLVER_H_
