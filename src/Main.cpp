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

#include "backtracker.h"
#include "edge_removal.h"
#include "graph.h"
#include "mpihandler.h"
#include "network.h"
#include "swing_surgery.h"
#include "reliability.h"
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

    return Network(N, terminals, edges);
}

void print_prob_test(std::vector< std::vector<int> > coeff)
{
    int E = coeff[0].size() - 1;
    for (int d = 0; d < (int)coeff.size(); d++) {
        int s = 0;
        for (int e = 0; e <= E; e++)
            s += coeff[d][e];
        cout << ((double) s) / (1 << E) << endl;
    }
}

int main(int argc, char **argv)
{
    /**
    vector< pair<int, int> > edges = {{3, 4}, {1, 2}, {3, 1}, {2, 0}, {1, 0}, {4, 2}};
    vector<int> terminals = {0, 4};

    Network g(5, terminals, edges);
    
    Backtracker bt(g, 0);
    bt.execute();

    std::vector< std::vector<int> > coeff = bt.get_coefficients();
    for (int d = 0; d < coeff.size(); d++) {
        for (int e = 0; e <= g.num_edges(); e++)
            cout << coeff[d][e] << " ";
        cout << endl;
    }
    */
    /*
    vector< pair<int, int> > edges_9_14 = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 5},
                                          {4, 5}, {2, 6}, {4, 6}, {7, 4}, {7, 3},
                                          {5, 6}, {6, 7}, {8, 4}, {8, 3}};
    */
    /*vector< pair<int, int> > edges_11_17 = {{0, 1}, {0, 2}, {0, 5}, {0, 7}, {0, 5},
                                            {8, 5}, {8, 7}, {8, 9}, {9, 4}, {1, 3},
                                            {2, 3}, {6, 3}, {4, 3}, {4, 6}, {4, 5},
                                            {5, 10}, {7, 10}};
   */                                         
   vector< pair<int, int> > edges_17_30 = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5},
                                           {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10},
                                           {0, 11}, {0, 12}, {0, 13}, {0, 14}, {0, 15},
                                           {16, 2}, {16, 3}, {16, 4}, {16, 5}, {16, 6},
                                           {16, 7}, {16, 8}, {16, 9}, {16, 10}, {1, 2},
                                           {3, 4}, {5, 6}, {7, 8}, {9, 10}, {11, 12}};
    vector<int> terminals = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    /**
    for (int i = 0; i < 17; i++)
        edges.emplace_back(edges[i].second, edges[i].first);
    
    Graph g(10, edges);

    cout << g.num_edges() << endl;

    vector<int> d = get_edge_distances(g, 0, 9);
    cout << d.size() << endl;
    for (int i = 0; i < (int) d.size(); i++)
        cout << d[i] << endl;    
    */
   
    int vert, edg;
   
    Graph g(17, edges_17_30, true);
    Network ng(g, terminals);
    MPIHandler mh(argc, argv, ng, 16);
    mh.execute();
    auto coeff = mh.get_coefficients();
    // print_prob_test(coeff);
    
    Swinger sw(&g);
    sw.swing(0, 16);

    Network ng2(g, terminals);
    MPIHandler mh2(argc, argv, ng2, 16);
    mh2.execute();
    auto coeff2 = mh2.get_coefficients();
    // print_prob_test(coeff);  

    for (auto j : coeff) {
        for (int i : j)
            cout << i << " ";
        cout << endl;
    }
    cout << endl;
    for (auto j : coeff2) {
        for (int i : j)
            cout << i << " ";
        cout << endl;
    }
    cout << endl;
    
    cout << "Enter the number of vertices: " << endl;
    cin >> vert;
    cout << "Enter the number of edges: " << endl;
    cin >> edg;

    d_comparison(vert, edg, coeff, coeff2); 

    /**
    vector< pair<int, int> > e = {{0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 3}, {3, 2},
                                  {3, 0}, {0, 3}, {0, 2}, {2, 0}, {1, 3}, {3, 1}};
    Graph g2(4, e);
    cout << "test" << endl;
    vector<int> d2 = get_edge_distances(g2, 0, 1);
    for (int i = 0; i < (int) d2.size(); i++)
        cout << d2[i] << endl;
    */
    return 0;

}
