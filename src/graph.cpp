/**
   @file Graph.cpp
   @author Luke Zeller

   Implementation of methods for class Graph, as defined
   in Graph.h
*/

#include <algorithm>
#include <queue>
#include <iostream>
#include "graph.h"

Edge::Edge(int v0, int v1)
    : v0(v0)
    , v1(v1) {}

int Edge::other(int v) const
{
    if (v == v0)
        return v1;
    if (v == v1)
        return v0;
    return -1;
}

Graph::Graph(int nodes, std::vector< std::pair<int, int> > edge_list)
    : N(nodes)
    , edges()
    , incident_id_list(N)
{
    for (int i = 0; i < (int) edge_list.size(); i++) {
        edges.emplace_back(edge_list[i].first, edge_list[i].second);
        incident_id_list[edge_list[i].second].push_back(i);
    }
}

int Graph::num_edges() const
{
    return (int) edges.size();
}

void Graph::print_graph() const
{
    std::cout << "---Printing Graph with " << N << " vertices---" << std::endl;
    for (int i = 0; i < num_edges(); i++) {
        std::cout << "--Edge " << i << ": " << edges[i].v0
                  << " " << edges[i].v1 << std::endl;
    }
    for (int i = 0; i < N; i++) {
        std::cout << "--Edges incident at vertex " << i << " :";
        for (int id : incident_id_list[i])
            std::cout << id << " ";
        std::cout << std::endl;
    }
}
