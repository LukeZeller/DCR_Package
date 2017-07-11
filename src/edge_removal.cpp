/**
   @file edge_removal.cpp
   @author Luke Zeller

   Functions to detect irrelevant edges using (naive) 
   Cycle-Cancelling algorithm to compute Min-Cost flow 
   on unit-capacity, unit-cost directed network.
**/

#ifdef _DEBUG_ER
#include <iostream>
#define PRINT(I) std::cout << I << std::endl;

#else
#define PRINT(I)

#endif

#include <algorithm>
#include <queue>
#include "graph_transform.h"
#include "flowgraph.h"

std::vector<int> get_edge_distances(const Graph& G, int v0, int v1)
{
    std::vector<int> dists(G.num_edges());
    Graph G_exp = expand_graph(G);
    
    for (int id = 0; id < G.num_edges(); id++) {
        FlowGraph G_flow(add_st(G_exp, G.edges_[id].v0, G.edges_[id].v1,
                                v0 + G.N_, v1 + G.N_));
        dists[id] = find_mcf(&G_flow) / 2 - 2;
    }
    return dists;
}
