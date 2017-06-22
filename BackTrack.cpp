/**
   @file backtrack.cpp
   @author Luke Zeller
   
   Definition of backtracking functions declared in
   backtrack.h
*/

#include "backtrack.h"

Backtracker::Backtracker(Graph &G, int level)
    : G(G)
    , level(level)
    , hasExecuted(false)
{
    dataMat = new int[G.getNodes() - 1][G.getEdges()]();
}

void Backtracker::recurse(int currLevel)
{   
    int d = G.getDiameter();

    if (d == -1)
        return;
    
    dataMat[d - 1][currLevel]++;
    
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
    //TODO
}
