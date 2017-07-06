CXX = mpic++
CC = mpic++
CXXFLAGS = -g -std=c++11 -Wall #-D_DEBUG_BT

Main: network.o graph.o backtracker.o mpihandler.o

Main.o: network.h backtracker.h mpihandler.h

network.o: network.h graph.h

graph.o: graph.h

mpihandler.o: mpihandler.h backtracker.h

backtracker.o: backtracker.h network.h

clean:
	rm -f *.o Main
