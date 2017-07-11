/**
   @file graph_transform.cpp
   @author Luke Zeller

   General suite of functions to apply transformations to
   graph objects.
*/

#include <vector>
#include "graph_transform.h"

//TODO: Implement to/from digraph
Graph to_digraph(Graph G)
{
    return G;
}

Graph from_digraph(Graph G)
{
    return G;
}

Graph expand_graph(Graph G)
{
    for (Edge& e : G.edges_)
        e.v0 += G.N_;

    for (int i = 0; i < G.N_; i++) {
        G.edges_.emplace_back(i, i + G.N_);
        G.incident_id_list_.push_back({G.num_edges() - 1});
    }
    G.N_ *= 2;
    return G;
}

Graph add_st(Graph G, int s0, int s1, int t0, int t1)
{
    G.edges_.emplace_back(G.N_, s0);
    G.incident_id_list_[s0].push_back(G.num_edges() - 1);

    G.edges_.emplace_back(G.N_, s1);
    G.incident_id_list_[s1].push_back(G.num_edges() - 1);

    G.edges_.emplace_back(t0, G.N_ + 1);
    G.edges_.emplace_back(t1, G.N_ + 1);
    G.incident_id_list_.push_back({});
    G.incident_id_list_.push_back(
        {G.num_edges() - 2, G.num_edges() - 1});

    G.N_ += 2;
    return G;
}
