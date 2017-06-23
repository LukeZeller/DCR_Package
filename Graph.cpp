/**
   @file Graph.cpp
   @author Luke Zeller

   Implementation of methods for class Graph, as defined
   in Graph.h
*/

#include <queue>
#include "Graph.h"

Edge::Edge(int v0, int v1)
    : v0(v0)
    , v1(v1)
    , isUP(true) {}

int Edge::other(int v) {
    if (v == v0)
        return v1;
    if (v == v1)
        return v0;
    return -1;
}

Graph::Graph(int nodes, int numTerminals, std::vector<int> terminals,
             std::vector< std::pair<int, int> > edgeList)
    : N(nodes)
    , K(numTerminals)
    , terminals(terminals)
    , edges()
    , incidentIDList(edgeList.size())
{
    for (int i = 0; i < edgeList.size(); i++) {
        edges.emplace_back(edgeList[i].first, edgeList[i].second);
        incidentIDList[edgeList[i].first].push_back(i);
        incidentIDList[edgeList[i].second].push_back(i);
    }
}

int Graph::getDiameter()
{
    return getDiameter(edges.size());
}

int Graph::getDiameter(int level)
{
    std::vector< std::vector<int> > dist(K, std::vector<int>(N));

    for (int t_i = 0; t_i < K; t_i++) {
        int root = terminals[t_i];

        bool visited[N] = {false};
        visited[root] = true;
        int nVisited = 1;
        
        std::queue<int> q;
        q.push(root);
        
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int ID : incidentIDList[u]) {
                if (ID >= level || !edges[ID].isUP)
                    continue;
                int v = edges[ID].other(u);
                if (!visited[v])  {
                    dist[t_i][v] = dist[t_i][u] + 1;
                    q.push(v);
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
            int dNew = dist[i][terminals[j]];
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
    return edges[edgeID].isUP;
}

void Graph::setState(int edgeID, bool isUP)
{
    edges[edgeID].isUP = isUP;
}
