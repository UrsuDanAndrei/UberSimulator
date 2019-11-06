// Copyright 2019 Ursu Dan-Andrei

#ifndef HASHSTRING_CPP_
#define HASHSTRING_CPP_

// functie de hashing de la std::string

#include <string>

#define P 31
#define M 1000000009

int hashString(std::string s) {
	int64_t h = 0, pow = 1;
	int l = s.size();
	for (int  i = 0; i < l; i++) {
		h = (h + 1LL * (s[i] - 'a' + 1) * pow) % M;
		pow = 1LL * (pow * P) % M;
	}

	return h;
}

#endif  // HASHSTRING_CPP_
