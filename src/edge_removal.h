/**
   @file edge_removal.h
   @author Luke Zeller

   Definition and documentation of functions to detect irrelevant
   edges using (naive) Cycle-Cancelling algorithm to compute 
   Min-Cost flow on unit-capacity, unit-cost directed network.
**/

#ifndef _EDGE_REMOVAL_H
#define _EDGE_REMOVAL_H

#include <vector>
#include "graph.h"

std::vector<int> get_edge_distances(const Graph& G, int v0, int v1);

#endif
