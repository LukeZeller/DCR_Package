/**
   @file graph.h
   @author Luke Zeller
   
   Definition of member functions and variables for
   Graph struct
*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <utility>

struct Edge {
    int v0, v1;

    Edge(int v0, int v1);
    int other(int v) const;
};

class Graph {
public:
    int N_;
    std::vector<Edge> edges_;
    std::vector< std::vector<int> > incident_id_list_;

    Graph(int nodes, std::vector< std::pair<int, int> > edge_list,
          bool is_undirected = false);

    int num_edges() const;
    void print_graph() const;
};

#endif
