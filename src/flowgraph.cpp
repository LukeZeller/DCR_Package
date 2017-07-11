/**
   @file flowgraph.cpp
   @author Luke Zeller

   Implementation of methods for FlowGraph struct.
*/

#include <algorithm>
#include <queue>
#include <vector>
#include "flowgraph.h"

int find_mcf(FlowGraph *FG)
{
    while (FG->add_path());
    while (FG->reduce_cycle());

    int mcf = 0;
    for (int c : FG->cost_)
        if (c < 0)
            mcf += 1;
    return mcf;
}

FlowGraph::FlowGraph(const Graph& G)
    : Graph(G)
    , cost_(G.num_edges(), 1) {}

bool FlowGraph::add_path()
{
    std::vector<int> pred(N_, -1);
    int s = N_ - 2,
        t = N_ - 1;

    std::queue<int> q;
    q.push(t);

    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int id : incident_id_list_[u]) {
            int v = edges_[id].other(u);
            if (pred[v] < 0)  {
                q.push(v);
                pred[v] = id;
            }
        }
    }

    if (pred[s] == -1)
        return false;
    
    int p, u = s;
    do {
        p = edges_[pred[u]].v1;
        flip_edge(pred[u]);
        cost_[pred[u]] *= -1;
        u = p;
    } while  (u != t);

    return true;
}

bool FlowGraph::reduce_cycle()
{
    std::vector<int> dist(N_, N_);
    std::vector<int> pred(N_, -1);
    int t = N_ - 1;
    dist[t] = 0;

    int v = -1;
    for (int itr = 0; itr < N_; itr++)
        for (int id = 0; id < num_edges(); id++)
            if (dist[edges_[id].v1] > dist[edges_[id].v0] + cost_[id]) {
                dist[edges_[id].v1] = dist[edges_[id].v0] + cost_[id];
                pred[edges_[id].v1] = id;
                if (itr == N_ - 1)
                    v = edges_[id].v1;
            }

    if (v == -1)
        return false;

    std::vector<bool> visited(N_, false);
    while (!visited[v]) {
        visited[v] = true;
        v = edges_[pred[v]].v0;
    }

    int p, u = v;
    do {
        p = edges_[pred[u]].v0;
        flip_edge(pred[u]);
        cost_[pred[u]] *= -1;
        u = p;
    } while  (u != v);

    return true;
}

void FlowGraph::flip_edge(int edge_id)
{
    auto& edge = edges_[edge_id];
    auto& in = incident_id_list_[edge.v1];
    in.erase(std::find(in.begin(), in.end(), edge_id));
    incident_id_list_[edge.v0].push_back(edge_id);
    edge.v0 ^= edge.v1;
    edge.v1 ^= edge.v0;
    edge.v0 ^= edge.v1;
}
