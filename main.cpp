// Copyright 2019 SD_Homework_Team

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>  // NOLINT(build/c++11)
#include "./solver.h"

float call_solver(std::ifstream& fin, int task, solver* s,
                  std::string filename) {
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> end;
	std::chrono::duration<double> elapsed;

    std::string task_name_out =
        "out/task_" + std::to_string(task) + "/" + filename + ".out";

	std::ofstream fout(task_name_out);
    if (!fout.is_open()) {
        std::cout << "Cannot open output file, check if directory exists!\n";
        return 0.0f;
    }

	switch (task) {
		case 1:
			start = std::chrono::high_resolution_clock::now();
			s->task1_solver(fin, fout);
			end = std::chrono::high_resolution_clock::now();
			break;
		case 2:
			start = std::chrono::high_resolution_clock::now();
			s->task2_solver(fin, fout);
			end = std::chrono::high_resolution_clock::now();
			break;
		case 3:
			start = std::chrono::high_resolution_clock::now();
			s->task3_solver(fin, fout);
			end = std::chrono::high_resolution_clock::now();
			break;
		case 4:
			start = std::chrono::high_resolution_clock::now();
			s->task4_solver(fin, fout);
			end = std::chrono::high_resolution_clock::now();
			break;
		case 5:
			start = std::chrono::high_resolution_clock::now();
			s->task5_solver(fin, fout);
			end = std::chrono::high_resolution_clock::now();
			break;
	}

	fout.close();

	elapsed = end - start;
	return (float)elapsed.count();
}

int main(int argc, char** argv) {
    // Usage : ./main file.in
    // Output: out/task_[1-5]/file.out

    if (argc != 2) {
        std::cout << "Incorrect number of arguments!\n";
        return 0;
    }
	solver* s = new solver();
    std::string in(argv[1]);
    std::string out = in.substr(in.find("/") + 1);
    out = out.substr(0, out.rfind("."));

	std::ifstream fin(argv[1]);
	if (!fin.is_open()) {
        std::cout << "Failed to open input file!\n";
        exit(1);
    }

    std::ofstream fout("time.out");

	float time_task_1;
	float time_task_2;
	float time_task_3;
	float time_task_4;
	float time_task_5;


	time_task_1 = call_solver(fin, 1, s, out);
	time_task_2 = call_solver(fin, 2, s, out);
	time_task_3 = call_solver(fin, 3, s, out);
	time_task_4 = call_solver(fin, 4, s, out);
	time_task_5 = call_solver(fin, 5, s, out);

	fout << time_task_1 * 1000 << "\n";
	fout << time_task_2 * 1000 << "\n";
	fout << time_task_3 * 1000 << "\n";
	fout << time_task_4 * 1000 << "\n";
	fout << time_task_5 * 1000  << "\n";

	fout.close();
	fin.close();

	delete s;

	return 0;
}
