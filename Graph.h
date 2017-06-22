/**
   @file Graph.h
   @author Luke Zeller
   
   Definition of member functions and variables for
   class Graph
*/

#ifndef _GRAPH_H
#define _GRAPH_H

static struct Edge {
    int u, v;
    bool isUP;
};

class Graph {
private:
    int N, K;
    std::vector<int> terminals;
    std::vector<Edge> edges;
    std::vector< std::vector<int> > adjList;
    
public:

    Graph(int nodes, int numTerminals; std::vector<int> terminals,
          std::vector< std::pair<int, int> > edgeList);

    
    int getDiameter();
    int getNodes();
    int getEdges();
    bool isUP(int edgeID);
    void setState(int edgeID, bool isUP);

};

#endif
