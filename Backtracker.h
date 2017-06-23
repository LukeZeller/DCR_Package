/**
   @file backtrack.h
   @author Luke Zeller


   Declaration and documentation of functions related
   to the backtracking procedure for the calculation of
   reliability polynomials.
*/

#ifndef _BACKTRACK_H
#define _BACKTRACK_H

#include "Graph.h"

class Backtracker {
    
    Graph& G;
    int baseDiam;
    int level;
    int **data;
    bool hasExecuted;
    
    void recurse(int level);

public:

    Backtracker(Graph& G, int level);

    void evecute();
    int **getCoefficients();
    
}

#endif
