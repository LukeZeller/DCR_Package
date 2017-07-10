/**
   @file mpihandler.h
   @author Luke Zeller

   MPIHandler is an object which performs distributes the
   backtracking procedure (of class Backtracker) on a 
   cluster and handles all the necessary MPI procedures.
*/

#ifndef _MPIHANDLER_H
#define _MPIHANDLER_H

#include <vector>
#include "network.h"
#include "mpi.h"

class MPIHandler
{
    Network& NG_;
    int diam_;
    std::vector< std::vector<int> > coeffs_;
    int p_count_, rank_;

public:
    MPIHandler(int argc, char **argv, Network& NG);
    MPIHandler(int argc, char **argv, Network& NG, int diam);
    ~MPIHandler();

    void execute();
    bool is_root();
    std::vector< std::vector<int> > get_coefficients();
};

#endif
