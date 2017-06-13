/**
   @file Graph.h
   @author Luke Zeller
   
   Definition of member functions and variables for
   class Graph
*/

class Graph {
private:
    int nodes;
    int *terminals;
    int **adjMatrix;

public:
    Graph(int nodes, int *terminals, int **adjMatrix);
};
