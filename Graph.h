/**
   @file Graph.h
   @author Luke Zeller
   
   Definition of member functions and variables for
   class Graph
*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <utility>

struct Edge {
    int v0, v1;
    bool isUP;

    Edge(int v0, int v1);
    int other(int v);    
};

class Graph {
private:
    int N, K;
    std::vector<int> terminals;
    std::vector<Edge> edges;
    std::vector< std::vector<int> > incidentIDList;
    
public:

    Graph(int nodes, int numTerminals, std::vector<int> terminals,
          std::vector< std::pair<int, int> > edgeList);

    int getDiameter();
    int getDiameter(int level);
    
    int getNodes();
    int getEdges();
    bool isUP(int edgeID);
    int getNumUP();
    void setState(int edgeID, bool isUP);

};

#endif
