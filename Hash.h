// Copyright 2019 Ursu Dan-Andrei

#ifndef HASH_H_
#define HASH_H_

// genereaza un dictionar de la TKey la TValue

#include <vector>
#include <list>
#include <utility>

template <typename TKey, typename TValue>
class Hash {
 public:
	int size;
	std::vector <std::list <std::pair < TKey, TValue > > > hashTabel;
	int (*hash)(TKey);

	// primeste o dimensiune pentru hashTabel si o functie de hashing
	Hash(int size, int (*hash)(TKey)) {
		this->size = size;
		hashTabel = std::vector<std::list<std::pair<TKey, TValue>>>(size);
		this->hash = hash;
	}

	Hash() {
	}

	~Hash() {
	}

	// copy-constructor
	Hash(const Hash& other) {
		size = other.size;
		hash = other.hash;

		hashTabel = other.hashTabel;
	}

	// copy assignment operator
	Hash& operator=(const Hash& other) {
		size = other.size;
		hash = other.hash;

		hashTabel = other.hashTabel;
		return *this;
	}

	// adauga o pereche cheie-valoare in hashTabel
	void addPair(const TKey& key, const TValue& val) {
		// daca cheia exista deja i se schimba valoarea
		int h = hash(key) % size;
		for (auto it = hashTabel[h].begin(); it != hashTabel[h].end(); ++it) {
			if (key == it->first) {
				it->second = val;
				return;
			}
		}

		// daca cheia nu exista se adauga perechea cheie-valoare
		hashTabel[h].push_back({key, val});
	}

	// sterge cheia key din dictionar
	void removeKey(const TKey& key) {
		int h = hash(key) % size;
		for (auto it = hashTabel[h].begin(); it != hashTabel[h].end(); ++it) {
			if (key == it->first) {
				hashTabel[h].erase(it);
				return;
			}
		}
	}

	// returneaza true daca exista cheia key
	bool hasKey(const TKey& key) {
		int h = hash(key) % size;
		for (auto it = hashTabel[h].begin(); it != hashTabel[h].end(); ++it) {
			if (key == it->first) {
				return true;
			}
		}

		return false;
	}

	// returneaza o referinta la valoarea din hashTabel corespunzatoare cheii
	TValue& operator[](const TKey& key) {
		int h = hash(key) % size;
		for (auto it = hashTabel[h].begin(); it != hashTabel[h].end(); ++it) {
			if (key == it->first) {
				return it->second;
			}
		}

		addPair(key, TValue{});
		return (hashTabel[h].rbegin()->second);
	}
};

#endif  // HASH_H_
