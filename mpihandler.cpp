/**
   @file mpihandler.cpp
   @author Luke Zeller

   Main procedure for backtracking execution on
   MPI systems.
*/

#include <iostream>
#include <string>
#include <vector>
#include "mpihandler.h"

void mpi_exec(int argc, char **argv, Graph& G, int diam)
{
    int p_count, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &p_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int p_itr = p_count, r_itr = rank + 1, level = 0;

    while (p_itr > 1) {
        int p_itr_new = p_itr/2;

        if (r_itr <= p_itr_new) {
            p_itr = p_itr_new;
            G.set_state(level, false);
        }
        else {
            r_itr -= p_itr_new;
            p_itr -= p_itr_new;
        }

        level++;
    }

    Backtracker bt(G, level, diam);
    bt.execute();

    auto coeff = bt.get_coefficients();

    int n = G.get_nodes(),
        e = G.get_edges();

    int coeff_buf[n][e + 1] = {{0}};
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= e; j++)
            coeff_buf[i][j] = coeff[i][j];

    int root_coeff_buf[n][e + 1];

    MPI_Reduce(&coeff_buf, &root_coeff_buf, n * (e + 1),
               MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= e; j++)
                std::cout << root_coeff_buf[i][j] << " ";
            std::cout << std::endl;
        }
    MPI_Finalize();
}
