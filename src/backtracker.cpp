/**
   @file backtracker.cpp
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
#include <vector>
#include "backtracker.h"
#include "network.h"

/** Free functions used locally as helpers */
static int combination(int N, int K)
{
    if (K == 0)
        return 1;
    return N * combination(N - 1, K - 1) / K;
}

/** Implementation of Constructors for class Backtracker */
Backtracker::Backtracker(Network& NG, int level, int diam_low)
    : Backtracker(NG, level, diam_low, NG.num_nodes() - 1) {}
Backtracker::Backtracker(Network& NG, int level, int diam_low, int diam_high)
    : NG_(NG)
    , base_diam_(std::max(diam_low, NG_.get_diameter()))
    , max_diam_(std::min(diam_high, NG_.num_nodes() - 1))
    , level_(level)
    , data_(NG.num_nodes() - base_diam_, std::vector<int>(NG.num_edges() + 1))
    , executed_(false) {}

/** Implementation of private member functions for Backtracker */
void Backtracker::recurse(int curr_level)
{   
    int d = NG_.get_diameter();

    if (d > max_diam_ || d == -1) {
        PRINT("Disconnected leaf reached: " << curr_level)
        return;
    }

    int num_up = NG_.num_up();

    if (curr_level == level_ || !NG_.is_up(curr_level - 1))
        data_[std::max(d - base_diam_, 0)][num_up]++;

    int d_base = NG_.get_diameter(curr_level);

    if (d_base >= 0 && d_base <= base_diam_) {
        PRINT("Connected leaf reached: " << curr_level) 
        for (int i = 1; i <= NG_.num_edges() - curr_level; i++)
            data_[0][num_up - i] += combination(NG_.num_edges() - curr_level, i);
    }

    else if (curr_level < NG_.num_edges()) {
        NG_.set_state(curr_level, false);
        recurse(curr_level + 1);

        NG_.set_state(curr_level, true);
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
    int E = NG_.num_edges();

    for (int d = 1; d < max_diam_ - base_diam_ + 1; d++)
        for (int e = 0; e < E + 1; e++)
            data_[d][e] += data_[d - 1][e];

    std::vector< std::vector<int> > coeff(base_diam_,
                                          std::vector<int>(E + 1));

    for (auto poly : data_)
        coeff.push_back(poly);

    return coeff;
}
