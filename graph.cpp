/**
   @file Graph.cpp
   @author Luke Zeller

   Implementation of methods for class Graph, as defined
   in Graph.h
*/

#include <algorithm>
#include <queue>
#include "graph.h"

Edge::Edge(int v0, int v1)
    : v0(v0)
    , v1(v1) {}

int Edge::other(int v) {
    if (v == v0)
        return v1;
    if (v == v1)
        return v0;
    return -1;
}

Graph::Graph(int nodes, std::vector< std::pair<int, int> > edge_list)
    : N(nodes)
    , edges()
    , incident_id_list(edge_list.size())
{
    for (int i = 0; i < edge_list.size(); i++) {
        edges.emplace_back(edge_list[i].first, edge_list[i].second);
        incident_id_list[edge_list[i].first].push_back(i);
        incident_id_list[edge_list[i].second].push_back(i);
    }
}
