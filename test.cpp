#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "Hash.h"
#include <utility>
#include "solver.h"

// int hash(std::string s) {
// 	int sum = 0, l = s.size();
// 	for (int i = 0; i < l; i++) {
// 		sum += s[i];
// 	}

// 	return sum;
// }
// int a(std::pair<int, int> s) {
// 	return s.first + s.second;
// }

// void b(int (*f)(std::string)) {
// 	int h = f(std::string("john"));
// 	std::cout << h;
// }

	std::ifstream in ("./in/test7.in");
	std::ofstream out("./out/task_1/test7.out");

	std::ofstream out2("./out/task_2/test7.out");
	std::ofstream out3("./out/task_3/test7.out");

int main() {
	/*Hash<std::string, int> h(666013, &hash);
	h.addPair(std::string("hei"), 2);
	h.addPair(std::string("1212"), 3);
	h.addPair(std::string("alo"), 4);
	h[std::string("ulala")] = 5;

	std::cout << h[std::string("hei")] << " " << h[std::string("1212")] << " " << h[std::string("alo")] << " " << h[std::string("ulala")]  << std::endl;

	h[std::string("ulala")] = 11;
	h.addPair(std::string("hei"), 3);
	h.removeKey(std::string("alo"));
	std::cout << h.hasKey(std::string("hei")) << " " << h.hasKey(std::string("alo")) << std::endl;

	std::cout << h[std::string("hei")] << " " << h[std::string("1212")] << " " << h[std::string("alo")] << " " << h[std::string("ulala")]  << std::endl;
	*/

	// std::cout << hashString(std::string("alexx")) << std::endl;
	// Graph<std::string> g(&hashString);

	// g.addNode(std::string("gabi"));
	// g.addNode(std::string("alex"));
	// g.addNode(std::string("alexx"));

	// g.addEdge(std::string("gabi"), std::string("alex"));
	// g.addEdge(std::string("gabi"), std::string("alexx"));
	// g.addEdge(std::string("alex"), std::string("alexx"));
	// g.addEdge(std::string("alex"), std::string("alexx"));
	// g.addEdge(std::string("alex"), std::string("alex"));



	// std::cout << g.bfs(std::string("gabi"), std::string("alex")) << std::endl;
	// std::cout << g.g[0].info << " ";

	// for (auto it = g.g[0].neighbours.begin(); it !=  g.g[0].neighbours.end(); it++) {
	// 	std::cout << (*it) << " ";
	// }

	// std::cout << std::endl;

	// std::cout << g.g[1].info << " ";

	// for (auto it = g.g[1].neighbours.begin(); it !=  g.g[1].neighbours.end(); it++) {
	// 	std::cout << (*it) << " ";
	// }

	// std::cout << std::endl;

	// std::cout << g.g[2].info << " ";

	// for (auto it = g.g[2].neighbours.begin(); it !=  g.g[2].neighbours.end(); it++) {
	// 	std::cout << (*it) << " ";
	// }

	// std::cout << std::endl;

	// g.removeEdge(std::string("gabi"), std::string("alexx"));

	// for (auto it = g.g[0].neighbours.begin(); it !=  g.g[0].neighbours.end(); it++) {
	// 	std::cout << (*it) << " ";
	// }

	// 	std::cout << std::endl;

	// g.reverseEdge(std::string("alex"), std::string("alexx"));

	// std::cout << g.g[0].info << " ";

	// for (auto it = g.g[0].neighbours.begin(); it !=  g.g[0].neighbours.end(); it++) {
	// 	std::cout << (*it) << " ";
	// }

	// std::cout << std::endl;

	// std::cout << g.g[1].info << " ";

	// for (auto it = g.g[1].neighbours.begin(); it !=  g.g[1].neighbours.end(); it++) {
	// 	std::cout << (*it) << " ";
	// }

	// std::cout << std::endl;

	// std::cout << g.g[2].info << " ";

	// for (auto it = g.g[2].neighbours.begin(); it !=  g.g[2].neighbours.end(); it++) {
	// 	std::cout << (*it) << " ";
	// }

	solver s;
	s.task1_solver(in, out);
	s.task2_solver(in, out2);
	s.task3_solver(in, out3);
	in.close();
	out.close();
	return 0;
}