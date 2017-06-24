/**
   @file backtrack.h
   @author Luke Zeller


   Declaration and documentation of functions related
   to the backtracking procedure for the calculation of
   reliability polynomials.
*/

#ifndef _BACKTRACK_H
#define _BACKTRACK_H

#include "graph.h"

class Backtracker {
    
    Graph& G_;
    int base_diam_, level_;
    std::vector< std::vector<int> > data_;
    bool executed_;
    
    void recurse(int level);

public:

    Backtracker(Graph& G);
    Backtracker(Graph& G, int level);
    Backtracker(Graph& G, int level, int diam);

    void execute();
    std::vector< std::vector<int> > get_coefficients();
    
};

#endif
