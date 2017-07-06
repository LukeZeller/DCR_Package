/**
   @file mcf.cpp
   @author Luke Zeller

   Functions to perform (naive) Cycle-Cancelling algorithm to
   compute Min-Cost flow on unit-capacity, unit-cost directed
   network.
**/

#include <vector>

std::vector<int> bf_find_neg_cycle()
