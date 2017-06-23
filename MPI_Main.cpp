/**
   @file MPI_Main.cpp
   @author Luke Zeller

   Main procedure for backtracking execution on
   MPI systems.
*/

#include "mpi.h"
#include "Graph.h"
#include "Backtracker.h"

int main(int argc, char **argv)
{
    int rank, P;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &P);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    

    MPI_Finalize();
    
}
