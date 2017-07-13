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

Swinger::Swinger(Graph* G)
    : G_(G) {}

void Swinger::pivot_edge(int edge_id, int v_old, int v_new)
{
    auto& inc_old = G_->incident_id_list_[v_old];

    inc_old.erase(std::find(inc_old.begin(), inc_old.end(), edge_id));
    G_->incident_id_list_[v_new].push_back(edge_id);

    auto& edge = G_->edges_[edge_id];
    if (edge.v0 == v_old)
        edge.v0 = v_new;
    else
        edge.v1 = v_new;
}

void Swinger::swing(int v_sup, int v_sub)
{
    std::vector<int> inc_sup = G_->incident_id_list_[v_sup],
                     inc_sub = G_->incident_id_list_[v_sub];

    inc_sup.pop_back();
    inc_sup.pop_back();
    for (int id_sup : inc_sup) {
        if (G_->edges_[id_sup].other(v_sup) == v_sub)
            continue;

        bool is_valid = true;
        for (int id_sub : inc_sub)
            if (G_->edges_[id_sup].other(v_sup) == G_->edges_[id_sub].other(v_sub)) {
                is_valid = false;
                break;
            }

        if (is_valid)
            pivot_edge(id_sup, v_sup, v_sub);
    }
}
