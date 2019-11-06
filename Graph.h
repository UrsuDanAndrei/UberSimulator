// Copyright 2019 Ursu Dan-Andrei

#ifndef GRAPH_H_
#define GRAPH_H_

// produce un graf cu noduri de tip T

#include <vector>
#include <queue>
#include <list>
#include "Node.h"
#include "Hash.h"
#include "hashString.cpp"
#ifndef H_SIZE
#define H_SIZE 666013
#endif  // H_SIZE

template <typename T>
class Graph {
 public:
	int nrNodes = 0;
	int nrEdges = 0;
	std::vector<Node<T>> g;
	std::vector<T> index2data;
	Hash<T, int> data2index;

	Graph() {
	}

	explicit Graph(int (*hashNodes)(T)) {
		 data2index = Hash<T, int>(H_SIZE, hashNodes);
	}

	~Graph() {
	}

	// copy-constructor
	Graph(const Graph& other) {
		nrNodes = other.nrNodes;
		nrEdges = other.nrEdges;

		index2data = other.index2data;
		data2index = other.data2index;
		g = other.g;
	}

	// copy assignment operator
	Graph& operator=(const Graph& other) {
		nrNodes = other.nrNodes;
		nrEdges = other.nrEdges;

		index2data = other.index2data;
		data2index = other.data2index;
		g = other.g;
		return (*this);
	}

	// adauga un nod cu informatia data in graf
	void addNode(const T& data) {
		data2index.addPair(data, nrNodes);
		index2data.push_back(data);

		Node<T> node;
		node.data = data;
		g.push_back(node);

		nrNodes++;
	}

	// adauga o muchie intre node1 si node2
	void addEdge(const T& node1, const T& node2) {
		int n1, n2;
		n1 = data2index[node1];
		n2 = data2index[node2];

		if (n1 == n2) {
			return;
		}

		g[n1].neighbours.push_back(n2);
		nrEdges++;
	}

	// sterge muchia dintre node1 si node2
	void removeEdge(const T& node1, const T& node2) {
		int n1, n2;
		n1 = data2index[node1];
		n2 = data2index[node2];

		// daca sunt mai multe muchii de la node1 la node2 se sterg toate
		auto it = g[n1].neighbours.begin();
		while (it != g[n1].neighbours.end()) {
			if (*it == n2) {
				auto itCopy = it;
				it++;
				g[n1].neighbours.erase(itCopy);
			} else {
				it++;
			}
		}
		nrEdges--;
	}

	// schimba sensul muchiei de la node1 la node2
	void reverseEdge(const T& node1, const T& node2) {
		bool edge12 = hasEdge(node1, node2);
		bool edge21 = hasEdge(node2, node1);

		// daca muchia e bidirectionala sau nu exista se ignora update-ul
		if (edge12 == edge21) {
			return;
		} else if (edge12 == true) {
			removeEdge(node1, node2);
			addEdge(node2, node1);
		} else {
			removeEdge(node2, node1);
			addEdge(node1, node2);
		}
	}

	// returneaza true daca exista muchie intre node1 si node2, false altfel
	bool hasEdge(const T& node1, const T& node2) {
		int n1, n2;
		n1 = data2index[node1];
		n2 = data2index[node2];

		for (auto it = g[n1].neighbours.begin();
			it != g[n1].neighbours.end(); ++it) {
			if (*it == n2) {
				return true;
			}
		}

		return false;
	}

	// returneaza numarul de muchii dintre nodurile start si end
	int getDist(const T& start, const T& end) {
		int n, n1, n2;
		n1 = data2index[start];
		n2 = data2index[end];

		// se face bfs din nodul de start
		std::queue<int> q;
		std::vector<int> dist(nrNodes, -1);
		q.push(n1);
		dist[n1] = 0;

		while (!q.empty()) {
			n = q.front();
			q.pop();

			// se opreste cand s-a gasit nodul de end
			if (n == n2) {
				break;
			}

			for (auto it = g[n].neighbours.begin();
				it != g[n].neighbours.end(); ++it) {
				// daca nodul n-a mai fost vizitat se adauga in coada
				if (dist[*it] == -1) {
					dist[*it] = dist[n] + 1;
					q.push(*it);
				}
			}
		}

		return dist[n2];
	}

	// returneaza indexul nodului cu informatia data
	int getNodeIndex(const T& data) {
		return data2index[data];
	}

	// produce vectorul de distante fata de nodul start
	void getDistAll(const int& start, std::vector<int>& dist) {
		// se face bfs din nodul de start
		std::queue<int> q;
		q.push(start);
		dist[start] = 0;
		int n;

		while (!q.empty()) {
			n = q.front();
			q.pop();

			for (auto it = g[n].neighbours.begin();
				it != g[n].neighbours.end(); ++it) {
				// daca nodul n-a mai fost vizitat se adauga in coada
				if (dist[*it] == -1) {
					dist[*it] = dist[n] + 1;
					q.push(*it);
				}
			}
		}
	}

	/* produce un vector cu nodurile destinatie, primite prin vectorul des, la
	care se poate ajunge, pornind din start si parcurgand maxEdges muchii*/
	void displayAllNeighbours(std::vector<T>& disp, const T& start, int maxEdges,
									const std::vector<T>& des,
									std::vector<int>& dist) {
		// se marcheaza posibilele destinatii cu -2
		for (auto it = des.begin(); it != des.end(); ++it) {
			dist[data2index[*it]] = -2;
		}

		// daca punctul de start este o destinatie se adauga la display
		if (dist[data2index[start]] == -2) {
			disp.push_back(start);
		}

		// se face bfs din nodul de start
		std::queue<int> q;
		q.push(data2index[start]);
		dist[data2index[start]] = 0;

		while (!q.empty()) {
			int n = q.front();
			q.pop();

			for (auto it = g[n].neighbours.begin();
				it != g[n].neighbours.end(); ++it) {
				if (dist[n] < maxEdges) {
					// daca nodul este marcat cu -2 se adauga la display
					if (dist[*it] == -2) {
						disp.push_back(getNodeData(*it));
						dist[*it] = dist[n] + 1;
						q.push(*it);
					}	else if (dist[*it] == -1) {
						dist[*it] = dist[n] + 1;
						q.push(*it);
					}
				}
			}
		}
	}

	// returneaza informatia din nodul cu index-ul index
	T getNodeData(int index) {
		return index2data[index];
	}

	// returneaza matricea de distante a grafului
	std::vector<std::vector<int>> getMDist() {
		std::vector<std::vector<int>> mDist;

		for (int i = 0; i < nrNodes; i++) {
			std::vector<int> dist(nrNodes, -1);
			getDistAll(i, dist);
			mDist.push_back(dist);
		}

		return mDist;
	}

	// returneaza lista de vecini directi ai nodului node
	std::list<int> getNodeNeighbours(const T& node) {
		return g[data2index[node]].neighbours;
	}
};

#endif  // GRAPH_H_
