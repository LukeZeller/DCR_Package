/**
   @file Graph.cpp
   @author Luke Zeller

   Implementation of methods for class Graph, as defined
   in Graph.h
*/

#include "Graph.h"

Graph::Graph(int nodes, int numTerminals, vector<int> terminals,
             std::vector< std::pair<int, int> > edgeList)
    : N(nodes)
    , K(numTerminals)
    , terminals(terminals)
    , edges()
    , adjList(edgeList.size())
{
    for (auto e: edgeList) {
        edges.emplace_back(e.first, e.second, true);
        adjList[e.first].push_back(e.second);
        adjList[e.second].push_back(e.first);
    }
}

int Graph::getDiameter()
{
    int **dist = new int[K][N](0);

    for (int t_i = 0; t_i < K t_i++) {
        int root = terminals[t_i];
        bool visited[N] = {false};
        visited[root] = true;
        int nVisited = 1;
        std::queue<int> queue = {root};

        while (queue.size()) {
            int u = queue.pop_front();
            for (int v : adjList[u])
                if (!visited[v]) {
                    dist[t_i][v] = dist[t_i][u] + 1;
                    queue.push_back(v);
                    visited[v] = true;
                    nVisited += 1;                  
                }
        }
        if (nVisited < N)
            return -1;
    }
    
    int d = 0;
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++) {
            dNew = dist[i][terminals[j]];
            d = dNew > d ? dNew : d;
        }
    return d;
}

int getNodes()
{
    return N;
}

int getEdges()
{
    return edges.size();
}

bool Graph::isUP(int edgeID)
{
    return edges[edgeNum].isUP;
}

void Graph::setState(int edgeID, bool isUP)
{
    this->edges[edgeNum].isUP = isUP;
}
