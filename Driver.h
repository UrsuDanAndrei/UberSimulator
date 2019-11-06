// Copyright 2019 Ursu Dan-Andrei

#ifndef DRIVER_H_
#define DRIVER_H_

// genereaza un sofer cu atibuele sale

#include <string>

struct Driver {
	int rating = 0;
	int dist = 0;
	int rides = 0;
	bool status = true;
	std::string junction;
	std::string name;
	float ratingAvg = 0.0;

	Driver(std::string name, std::string junction) {
		this->name = name;
		this->junction = junction;
	}

	~Driver() {
	}

	// copy-constructor
	Driver(const Driver& other) {
		rating = other.rating;
		dist = other.dist;
		rides = other.rides;
		status = other.status;
		junction = other.junction;
		name = other.name;
		ratingAvg = other.ratingAvg;
	}

	// copy assignment operator
	Driver& operator=(const Driver& other) {
		rating = other.rating;
		dist = other.dist;
		rides = other.rides;
		status = other.status;
		junction = other.junction;
		name = other.name;

		ratingAvg = other.ratingAvg;
		return *this;
	}

	// cel mai mic sofer este cel cu rating-ul cel mai bun si numele cel mai mic
	bool operator<(const Driver& other) {
		if (ratingAvg == other.ratingAvg) {
			return name < other.name;
		} else {
			return ratingAvg > other.ratingAvg;
		}
	}

	bool operator>(const Driver& other) {
		return !(*this < other);
	}
};



#endif  // DRIVER_H_
