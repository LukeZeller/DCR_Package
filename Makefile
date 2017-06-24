CXX = mpic++
CC = mpic++
CXXFLAGS = -g -std=c++11 -Wall #-D_DEBUG_BT

Main: graph.o backtracker.o mpihandler.o

Main.o: graph.h backtracker.h mpihandler.h

graph.o: graph.h

backtracker.o: backtracker.h graph.h

clean:
	rm -f *.o Main
