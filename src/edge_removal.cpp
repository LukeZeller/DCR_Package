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
#include "edge_removal.h"

std::vector<int> get_edge_distances(const Graph& G, int v0, int v1)
{
    std::vector<int> dists(G.num_edges());
    Graph G_exp = expand_graph(G);
    
    for (int id = 0; id < G.num_edges(); id++) {
        Graph G_flow = add_st(G_exp, G.edges[id].v0, G.edges[id].v1,
                              v0 + G.N, v1 + G.N);
        //G_flow.print_graph();
        dists[id] = find_mcf(G_flow) / 2 - 2;
    }
    return dists;
}

Graph expand_graph(const Graph& G)
{
    Graph G_new(G);
    G_new.N *= 2;

    for (Edge& e : G_new.edges)
        e.v0 += G.N;

    for (int i = 0; i < G.N; i++) {
        G_new.edges.emplace_back(i, i + G.N);
        G_new.incident_id_list.push_back({G_new.num_edges() - 1});
    }
    return G_new;
}

Graph add_st(const Graph& G, int s0, int s1, int t0, int t1)
{
    Graph G_new(G);
    G_new.N += 2;

    G_new.edges.emplace_back(G.N, s0);
    G_new.incident_id_list[s0].push_back(G_new.num_edges() - 1);

    G_new.edges.emplace_back(G.N, s1);
    G_new.incident_id_list[s1].push_back(G_new.num_edges() - 1);

    G_new.edges.emplace_back(t0, G.N + 1);
    G_new.edges.emplace_back(t1, G.N + 1);
    G_new.incident_id_list.push_back({});
    G_new.incident_id_list.push_back(
        {G_new.num_edges() - 2, G_new.num_edges() - 1});

    return G_new;
}

int find_mcf(const Graph& G)
{
    Graph G_res(G);
    std::vector<int> cost(G.num_edges(), 1);
    
    while (add_path(G_res, cost)) {G_res.print_graph();}
    //std::cout << "derp" << std::endl;
    while (reduce_cycle(G_res, cost)) {G_res.print_graph();}

    int mcf = 0;
    for (int c : cost)
        if (c < 0)
            mcf += 1;
    return mcf;
}

bool add_path(Graph& res, std::vector<int>& cost)
{
    std::vector<int> pred(res.N, -1);
    int s = res.N - 2,
        t = res.N - 1;

    std::queue<int> q;
    q.push(t);

    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int id : res.incident_id_list[u]) {
            int v = res.edges[id].other(u);
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
        p = res.edges[pred[u]].v1;
        flip_edge(res, pred[u]);
        cost[pred[u]] *= -1;
        u = p;
    } while  (u != t);
    
    return true;
}

bool reduce_cycle(Graph& res, std::vector<int>& cost)
{
    std::vector<int> dist(res.N, res.N);
    std::vector<int> pred(res.N, -1);
    int t = res.N - 1;
    dist[t] = 0;

    int v = -1;
    for (int itr = 0; itr < res.N; itr++)
        for (int id = 0; id < res.num_edges(); id++)
            if (dist[res.edges[id].v1] > dist[res.edges[id].v0] + cost[id]) {
                dist[res.edges[id].v1] = dist[res.edges[id].v0] + cost[id];
                pred[res.edges[id].v1] = id;
                if (itr == res.N - 1)
                    v = res.edges[id].v1;
            }

    if (v == -1)
        return false;

    std::vector<bool> visited(res.N, false);
    while (!visited[v]) {
        visited[v] = true;
        v = res.edges[pred[v]].v0;
    }

    int p, u = v;
    do {
        p = res.edges[pred[u]].v0;
        flip_edge(res, pred[u]);
        cost[pred[u]] *= -1;
        u = p;
    } while  (u != v);

    return true;
}

void flip_edge(Graph& G, int edge_id)
{
    auto& edge = G.edges[edge_id];
    auto& in = G.incident_id_list[edge.v1];
    in.erase(std::find(in.begin(), in.end(), edge_id));
    G.incident_id_list[edge.v0].push_back(edge_id);
    edge.v0 ^= edge.v1;
    edge.v1 ^= edge.v0;
    edge.v0 ^= edge.v1;
}
