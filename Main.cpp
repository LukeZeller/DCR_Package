/**
   @file Main.cpp
   @author Luke Zeller
   
   Implementation of main() for program - reads input,
   builds data structures, calls helper functions as
   necessary.
*/

#include <iostream>
//#include <fstream>
#include <cstdlib>
#include <vector>
#include <utility>
#include "Graph.h"
#include "Backtracker.h"

using namespace std;

int main()
{
    vector< pair<int, int> > edges = {{3, 4}, {1, 2}, {3, 1}, {2, 0}, {1, 0}, {4, 2}};
    vector<int> terminals = {0, 4};

    Graph g(5, 2, terminals, edges);

    cout << g.getDiameter() << endl;

    for (int i = 0; i <= 6; i++)
        cout << g.getDiameter(i) << endl;
    
    Backtracker bt(g, 0);
    bt.execute();
    cout << "Finished" << endl;
    std::vector< std::vector<int> > coeff = bt.getCoefficients();

    for (int d = 0; d < g.getNodes(); d++) {
        for (int e = 0; e <= g.getEdges(); e++)
            cout << coeff[d][e] << " ";
        cout << endl;
    }
    
    return 0;
}
