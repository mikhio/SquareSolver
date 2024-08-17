cpp_files := main.cpp SqEquation.cpp

all:
	make clean
	make compile
	make run
clean:
	rm -rf ./build/*
compile: $(cpp_files) 
	clear
	g++ -std=c++11 $(cpp_files) -o build/SquareSolver -Wall
run:
	build/SquareSolver
