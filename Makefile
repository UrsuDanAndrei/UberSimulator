
build:
	g++ --std=c++11 -Wall -Wextra main.cpp -o exec

.PHONY: clean

run:
	./main

clean:
	rm out/*/*
	rm exec
	rm time.out
