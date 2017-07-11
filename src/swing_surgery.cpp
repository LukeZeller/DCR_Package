/**
   @file swing_surgery.cpp
   @author Luke Zeller

   Implementation of functions to perform swing surgery 
   on an arbitrary input graph, if possible.
*/

#include <algorithm>
#include <vector>
#include "graph.h"
#include "swing_surgery.h"

static std::vector<int> neighbors(const Graph& G, int v)
{
    std::vector<int> neighbors;
    auto& inc_v = G.incident_id_list_[v];

    for (int id : inc_v)
        neighbors.push_back(G.edges_[id].other(v));

    std::sort(neighbors.begin(), neighbors.end());
    return neighbors;
}

Graph manual_swing(Graph G)
{
    return manual_swing(G, G.N_ - 1, G.N_ - 2);
}

//TODO: Finish implementation
Graph manual_swing(Graph G, int a, int b)
{
    std::vector<int> nh_a = neighbors(G, a), nh_b = neighbors(G, b);
    //if (std::includes(nh_a.begin(), nh_a.end(), nh_b.begin(), nh_b.end());
    return G;
}
