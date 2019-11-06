#ifndef __HASHEDGES_H__
#define __HASHEDGES_H__

#include <string>

int hashEdges(std::pair<int, int> p) {
	return p.first ^ p.second;
}

#endif // __HASHEDGES_H__