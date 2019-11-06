// Copyright 2019 Ursu Dan-Andrei

#ifndef NODE_H_
#define NODE_H_

#include <list>

template <typename T>
struct Node {
	T data;
	std::list<int> neighbours;
};

#endif  // NODE_H_
