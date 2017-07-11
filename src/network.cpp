/**
   @file network.cpp
   @author Luke Zeller
   
   Implementation of methods for class Network, as defined
   in network.h
*/

#include <algorithm>
#include <queue>
#include "network.h"

Network::Network(int nodes, std::vector<int> terminals,
             std::vector< std::pair<int, int> > edge_list)
    : Graph(nodes, edge_list, true)
    , is_up_(edge_list.size(), true)
    , K_(terminals.size())
    , terminals_(terminals) {}

Network::Network(const Graph& G, std::vector<int> terminals)
    : Graph(G)
    , is_up_(G.num_edges(), true)
    , K_(terminals.size())
    , terminals_(terminals) {}

int Network::num_nodes() const
{
    return N_;
}

int Network::get_diameter() const
{
    return get_diameter(num_edges());
}

int Network::get_diameter(int level) const
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
                if (id >= level || !is_up_[id])
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

int Network::num_up() const
{
    int c = 0;
    for (int i = 0; i < num_edges(); i++)
        if (is_up_[i])
            c++;
    return c;
}

bool Network::is_up(int edge_id) const
{
    return is_up_[edge_id];
}

void Network::set_state(int edge_id, bool new_state)
{
    is_up_[edge_id] = new_state;
}
