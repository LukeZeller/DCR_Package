/**
   @file graph_transform.h
   @author Luke Zeller

   Declaration and documentation of graph transformation
   helper functions.
*/

#include "graph.h"

Graph to_digraph(Graph G);

Graph from_digraph(Graph G);

Graph expand_graph(Graph G);

Graph add_st(Graph G, int s0, int s1, int t0, int t1);
