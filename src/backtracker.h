/**
   @file backtrack.h
   @author Luke Zeller


   Declaration and documentation of Backtracker object
   for the calculation of reliability polynomials.
*/

#ifndef _BACKTRACK_H
#define _BACKTRACK_H

#include "network.h"

class Backtracker {
    
    Network& NG_;
    int base_diam_, level_;
    std::vector< std::vector<int> > data_;
    bool executed_;
    
    void recurse(int level);

public:

    Backtracker(Network& NG);
    Backtracker(Network& NG, int level);
    Backtracker(Network& NG, int level, int diam);

    void execute();
    std::vector< std::vector<int> > get_coefficients();

};

#endif
