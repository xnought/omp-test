all: build run

build:
	clang++ -std=c++17 -fopenmp main.cpp

run:
	./a.out