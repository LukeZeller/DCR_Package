/**
   @file Graph.cpp
   @author Luke Zeller

   Implementation of methods for class Graph, as defined
   in Graph.h
*/

#include "Graph.h"

int Edge::other(int v) {
    if (v == v0)
        return v1;
    if (v == v1)
        return v0;
    return -1;
}

Graph::Graph(int nodes, int numTerminals, vector<int> terminals,
             std::vector< std::pair<int, int> > edgeList)
    : N(nodes)
    , K(numTerminals)
    , terminals(terminals)
    , edges()
    , incidentIDList(edgeList.size())
{
    for (int i = 0; i < edgeList.size(); i++) {
        edges.emplace_back(edgeList[i].first, edgeList[i].second, true);
        incidentIDList[e.first].push_back(i);
        incidentIDList[e.second].push_back(i);
    }
}

int Graph::getDiameter(int level = edges.size())
{
    int **dist = new int[K][N](0);

    for (int t_i = 0; t_i < K; t_i++) {
        int root = terminals[t_i];
        bool visited[N] = {false};
        visited[root] = true;
        int nVisited = 1;
        std::queue<int> queue = {root};
 
        while (queue.size()) {
            int u = queue.pop_front();
            for (int ID : adjList[u]) {
                int v = edgeList[ID].other(u);
                if (ID < level && !visited[v])  {
                    dist[t_i][v] = dist[t_i][u] + 1;
                    queue.push_back(v);
                    visited[v] = true;
                    nVisited += 1;
                }
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

int Graph::getNodes()
{
    return N;
}

int Graph::getEdges()
{
    return edges.size();
}

bool Graph::isUP(int edgeID)
{
    return edges[edgeNum].isUP;
}

void Graph::setState(int edgeID, bool isUP)
{
    edges[edgeNum].isUP = isUP;
}
