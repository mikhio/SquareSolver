all: sq.cpp
	make compile
	make run
compile: sq.cpp
	g++ -std=c++11 sq.cpp -o build/sq -Wall
run:
	clear
	build/sq
