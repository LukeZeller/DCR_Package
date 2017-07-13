/**
   @file swing_surgery.h
   @author Luke Zeller

   Definition and documentation of functions to perform
   swing surgery on an arbitrary input graph, if possible.
*/

#include "graph.h"

class Swinger
{
    Graph* G_;
    
public:
    Swinger(Graph* G);

    void pivot_edge(int edge_id, int v_old, int v_new);
    void swing(int v_sup, int v_sub);
};
