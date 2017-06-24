/**
   @file backtrack.cpp
   @author Luke Zeller
   
   Definition of backtracking functions declared in
   backtrack.h
*/

/** Print info for debugging */
#ifdef _DEBUG_BT
#include <iostream>
#define PRINT(I) std::cout << I << std::endl;

#else
#define PRINT(I)

#endif

#include <algorithm>
#include "backtracker.h"

/** Free functions used locally as helpers */
static int combination(int N, int K)
{
    if (K == 0)
        return 1;
    return N * combination(N - 1, K - 1) / K;
}

/** Implementation of Constructors for class Backtracker */
Backtracker::Backtracker(Graph& G)
    : Backtracker(G, 0, 0) {}

Backtracker::Backtracker(Graph& G, int level)
    : Backtracker(G, level, 0) {}

Backtracker::Backtracker(Graph& G, int level, int diam)
    : G_(G)
    , base_diam_(std::max(diam, G.get_diameter()))
    , level_(level)
    , data_(G.get_nodes() - base_diam_, std::vector<int>(G.get_edges() + 1))
    , executed_(false) {}

/** Implementation of private member functions for Backtracker */
void Backtracker::recurse(int curr_level)
{   
    int d = G_.get_diameter();
    
    if (d == -1) {
        PRINT("Disconnected leaf reached: " << curr_level)
        return;
    }
    
    int num_up = G_.get_num_up();

    if (curr_level == level_ || !G_.is_up(curr_level - 1))
        data_[std::max(d - base_diam_, 0)][num_up]++;

    int d_base = G_.get_diameter(curr_level);

    if (d_base >= 0 && d_base <= base_diam_) {
        PRINT("Connected leaf reached: " << curr_level) 
        for (int i = 1; i <= G_.get_edges() - curr_level; i++)
            data_[0][num_up - i] += combination(G_.get_edges() - curr_level, i);
    }

    else if (curr_level < G_.get_edges()) {
        G_.set_state(curr_level, false);
        recurse(curr_level + 1);

        G_.set_state(curr_level, true);
        recurse(curr_level + 1);
    }
}

/** Implementation of public member functions for Backtracker */
void Backtracker::execute()
{
    if (!executed_) {
        executed_ = true;
        PRINT("Execution begun")
        recurse(level_);
    }
}

std::vector< std::vector<int> > Backtracker::get_coefficients()
{
    int N = G_.get_nodes(), E = G_.get_edges();

    for (int d = 1; d < N - base_diam_; d++)
        for (int e = 0; e < E + 1; e++)
            data_[d][e] += data_[d - 1][e];

    std::vector< std::vector<int> > coeff(base_diam_,
                                          std::vector<int>(E + 1));

    for (auto poly : data_)
        coeff.push_back(poly);

    return coeff;
}
