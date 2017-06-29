/**
   @file mpihandler.cpp
   @author Luke Zeller

   Implementation of MPIHandler class, used to perform backtracking
   calculations using MPI on a cluster.
*/

#include <vector>
#include "backtracker.h"
#include "mpihandler.h"

MPIHandler::MPIHandler(int argc, char **argv, Graph& G)
    : MPIHandler(argc, argv, G, 0) {}

MPIHandler::MPIHandler(int argc, char **argv, Graph& G, int diam)
    : G_(G)
    , diam_(diam)
    , coeffs_(G.get_nodes(), std::vector<int>(G.get_edges() + 1))
    , p_count_()
    , rank_()
{
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &p_count_);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_);
}

MPIHandler::~MPIHandler()
{
    MPI_Finalize();
}

void MPIHandler::execute()
{
    int p_itr = p_count_, r_itr = rank_ + 1, level = 0;

    while (p_itr > 1) {
        int p_itr_new = p_itr/2;

        if (r_itr <= p_itr_new) {
            p_itr = p_itr_new;
            G_.set_state(level, false);
        }
        else {
            r_itr -= p_itr_new;
            p_itr -= p_itr_new;
        }

        level++;
    }

    Backtracker bt(G_, level, diam_);
    bt.execute();

    auto coeff = bt.get_coefficients();

    int n = G_.get_nodes(),
        e = G_.get_edges();

    int send_coeff_buf[n][e + 1];
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= e; j++)
            send_coeff_buf[i][j] = coeff[i][j];

    int recv_coeff_buf[n][e + 1];

    MPI_Allreduce(&send_coeff_buf, &recv_coeff_buf, n * (e + 1),
                  MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= e; j++)
            coeffs_[i][j] = recv_coeff_buf[i][j];
}

bool MPIHandler::is_root()
{
    return rank_ == 0;
}

std::vector< std::vector<int> > MPIHandler::get_coefficients()
{
    return coeffs_;
}
