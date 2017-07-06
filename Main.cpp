/**
   @file Main.cpp
   @author Luke Zeller
   
   Implementation of main() for program - reads input,
   builds data structures, calls helper functions as
   necessary.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <utility>
#include "network.h"
#include "backtracker.h"
#include "mpihandler.h"

using namespace std;

Network input_net(string in)
{
    ifstream fin(in);

    int N, K, E;
    fin >> N >> K >> E;

    vector<int> terminals(K);
    vector< pair<int, int> > edges(E);

    for (int i = 0; i < K; i++)
        fin >> terminals[i];

    for (int i = 0; i < E; i++)
        fin >> edges[i].first >> edges[i].second;

    return Network(N, K, terminals, edges);
}

int main(int argc, char **argv)
{
    /**
    vector< pair<int, int> > edges = {{3, 4}, {1, 2}, {3, 1}, {2, 0}, {1, 0}, {4, 2}};
    vector<int> terminals = {0, 4};

    Graph g(5, 2, terminals, edges);

    cout << g.get_diameter() << endl;

    for (int i = 0; i <= 6; i++)
        cout << g.get_diameter(i) << endl;
    
    Backtracker bt(g, 0, 1);
    bt.execute();
    cout << "Finished" << endl;

    std::vector< std::vector<int> > coeff = bt.get_coefficients();
    for (int d = 0; d < coeff.size(); d++) {
        for (int e = 0; e <= g.get_edges(); e++)
            cout << coeff[d][e] << " ";
        cout << endl;
    }
    */
    vector< pair<int, int> > edges = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5},
                                      {0, 6}, {0, 7}, {0, 8}, {9, 2}, {9, 3},
                                      {9, 4}, {9, 5}, {9, 6}, {1, 2}, {1, 3},
                                      {2, 4}, {3, 7}};
    vector<int> terminals = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    Network g(10, 10, terminals, edges);
    
    MPIHandler mh(argc, argv, g, 1);
    mh.execute();

    auto coeff = mh.get_coefficients();

    if (mh.is_root())
        for (int d = 0; d < coeff.size(); d++) {
            int s = 0;
            for (int e = 0; e <= g.get_edges(); e++)
                s += coeff[d][e];
            cout << ((double) s) / (1 << g.get_edges()) << endl;
        }
    
    return 0;
}
