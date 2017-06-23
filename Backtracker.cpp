/**
   @file backtrack.cpp
   @author Luke Zeller
   
   Definition of backtracking functions declared in
   backtrack.h
*/

#include "Backtracker.h"

Backtracker::Backtracker(Graph &G, int level)
    : G(G)
    , baseDiam(G.getDiameter())
    , level(level)
    , hasExecuted(false)
{
    data = new int[G.getNodes() - baseDiam][G.getEdges() + 1]();
}

void Backtracker::recurse(int currLevel)
{
    //TODO
    //int dBase = G.getDiameter(currLevel);
    
    int d = G.getDiameter();

    if (d == -1)
        return;

    if (currLevel == 0 || !G.getState(currLevel - 1))
        data[d - baseDiam - 1][currLevel]++;
    
    G.setState(currLevel, false);
    recurse(currLevel + 1);

    G.setState(currLevel, true);
    recurse(currLevel + 1)
}

void Backtracker::execute()
{
    if (!hasExecuted) {
        hasExecuted = true;
        recurse(level);
    }

int **Backtracker::getCoefficients()
{
    int N = G.getNodes(), E = G.getEdges();
    int **coeff = new int[N - 1][E + 1](0);

    for (int e = 0; e < E + 1; e++)
        coeffMat[N - 1][e] = dataMat[N - baseDiam - 1][e];

    for (int d = N - 2; d > N - baseDiam; d++)
        for (int e = 0; e < E + 1; e++)
            coeff[d][e] = coeff[d + 1][e] + data[d - baseDiam][e];

    return coeff;
}
