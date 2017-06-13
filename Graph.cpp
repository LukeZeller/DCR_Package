/**
   @file Graph.cpp
   @author Luke Zeller

   Implementation of methods for class Graph, as defined
   in Graph.h
*/

#include "Graph.h"

Graph::Graph(int nodes, int *terminals, int **adjMatrix)
    : nodes(nodes)
    , terminals(terminals)
    , adjMatrix(adjMatrix)
{}
