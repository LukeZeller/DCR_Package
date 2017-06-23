CXX = g++
CC = g++
CXXFLAGS = -g -std=c++11 -Wall

Main: Graph.o Backtracker.o

Main.o: Backtracker.h Graph.h

Backtracker.o: Backtracker.h Graph.h

Graph.o: Graph.h

clean:
	rm -f *.o Main
