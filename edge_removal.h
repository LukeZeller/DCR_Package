/**
   @file edge_removal.h
   @author Luke Zeller

   Definition and documentation of functions to detect irrelevant
   edges using (naive) Cycle-Cancelling algorithm to compute 
   Min-Cost flow on unit-capacity, unit-cost directed network.
**/

#include <vector>
#include "graph.h"

std::vector<int> get_edge_distances(const Graph& G, int v0, int v1);

Graph expand_graph(const Graph& G);

Graph add_st(const Graph& G, int s0, int s1, int t0, int t1);

int find_mcf(const Graph& G);

bool add_path(Graph& res, std::vector<int>& cost);
    
bool reduce_cycle(Graph& res, std::vector<int>& cost);

void flip_edge(Graph& G, int edge_id);
