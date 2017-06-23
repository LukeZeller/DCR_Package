/**
   @file backtrack.cpp
   @author Luke Zeller
   
   Definition of backtracking functions declared in
   backtrack.h
*/

#include <iostream>
#include "Backtracker.h"

Backtracker::Backtracker(Graph &G, int level)
    : G(G)
    , baseDiam(G.getDiameter())
    , level(level)
    , data(G.getNodes() - baseDiam, std::vector<int>(G.getEdges() + 1))
    , hasExecuted(false) {}

void Backtracker::recurse(int currLevel)
{

    std::cout << "Recursion at level " << currLevel << std::endl;
    
    //TODO
    //int dBase = G.getDiameter(currLevel);
    
    int d = G.getDiameter();

    std::cout << "In this state graph has diameter " << d << std::endl;
    
    if (d == -1)
        return;

    
    
    if (currLevel == 0 || !G.isUP(currLevel - 1))
        data[d - baseDiam][currLevel]++;

    if (currLevel < G.getEdges()) {
        G.setState(currLevel, false);
        recurse(currLevel + 1);

        G.setState(currLevel, true);
        recurse(currLevel + 1);
    }
}

void Backtracker::execute()
{
    if (!hasExecuted) {
        hasExecuted = true;
        std::cout << "Execution begun" << std::endl;
        recurse(level);
    }
}

std::vector< std::vector<int> > Backtracker::getCoefficients()
{
    int N = G.getNodes(), E = G.getEdges();
    std::vector< std::vector<int> > coeff(N, std::vector<int>(E + 1));

    for (int e = 0; e < E + 1; e++)
        coeff[N - 1][e] = data[N - baseDiam - 1][e];

    for (int d = N - 2; d > N - baseDiam; d++)
        for (int e = 0; e < E + 1; e++)
            coeff[d][e] = coeff[d + 1][e] + data[d - baseDiam][e];

    return coeff;
}
