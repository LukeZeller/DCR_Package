CXX = mpic++
CC = mpic++
CXXFLAGS = -g -std=c++11 -Wall -D_DEBUG_ER

Main: network.o graph.o backtracker.o mpihandler.o edge_removal.o

Main.o: network.h backtracker.h mpihandler.h edge_removal.h

network.o: network.h graph.h

graph.o: graph.h

backtracker.o: backtracker.h network.h

mpihandler.o: mpihandler.h backtracker.h

edge_removal.o: edge_removal.h graph.h

clean:
	rm -f *.o Main
