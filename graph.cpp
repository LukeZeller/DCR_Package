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
    , v1(v1)
    , is_up(true) {}

int Edge::other(int v) {
    if (v == v0)
        return v1;
    if (v == v1)
        return v0;
    return -1;
}

Graph::Graph(int nodes, int num_terminals, std::vector<int> terminals,
             std::vector< std::pair<int, int> > edge_list)
    : N_(nodes)
    , K_(num_terminals)
    , terminals_(terminals)
    , edges_()
    , incident_id_list_(edge_list.size())
{
    for (int i = 0; i < edge_list.size(); i++) {
        edges_.emplace_back(edge_list[i].first, edge_list[i].second);
        incident_id_list_[edge_list[i].first].push_back(i);
        incident_id_list_[edge_list[i].second].push_back(i);
    }
}

int Graph::get_diameter()
{
    return get_diameter(edges_.size());
}

int Graph::get_diameter(int level)
{
    std::vector< std::vector<int> > dist(K_, std::vector<int>(N_));

    for (int t_i = 0; t_i < K_; t_i++) {
        int root = terminals_[t_i];

        bool visited[N_] = {false};
        visited[root] = true;
        
        std::queue<int> q;
        q.push(root);
        
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int id : incident_id_list_[u]) {
                if (id >= level || !edges_[id].is_up)
                    continue;
                int v = edges_[id].other(u);
                if (!visited[v])  {
                    dist[t_i][v] = dist[t_i][u] + 1;
                    q.push(v);
                    visited[v] = true;
                }
            }
        }
        for (int v : terminals_)
            if (!visited[v])
                return -1;
    }
    
    int d = 0;
    for (int i = 0; i < K_; i++)
        for (int j = 0; j < K_; j++)
            d = std::max(dist[i][terminals_[j]], d);
    return d;
}

int Graph::get_nodes()
{
    return N_;
}

int Graph::get_edges()
{
    return edges_.size();
}

int Graph::get_num_up()
{
    int c = 0;
    for (Edge e: edges_)
        if (e.is_up)
            c++;
    return c;
}

bool Graph::is_up(int edge_id)
{
    return edges_[edge_id].is_up;
}

void Graph::set_state(int edge_id, bool new_state)
{
    edges_[edge_id].is_up = new_state;
}
