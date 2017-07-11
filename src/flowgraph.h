/**
   @file flowgraph.h
   @author Luke Zeller
   
   Definition of member functions and variables for
   FlowGraph struct, an extention of the graph struct
   
*/

#ifndef _FLOWGRAPH_H
#define _FLOWGRAPH_H

#include <vector>
#include "graph.h"

class FlowGraph : public Graph {
public:
    std::vector<int> cost_;

    FlowGraph(const Graph& G);

    bool add_path();
    bool reduce_cycle();
    void flip_edge(int edge_id);
};

int find_mcf(FlowGraph* FG);

#endif
