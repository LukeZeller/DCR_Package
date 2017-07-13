/**
   @file network.h
   @author Luke Zeller
   
   Definition of member functions and variables for the
   Network class
*/

#ifndef _NETWORK_H
#define _NETWORK_H

#include <vector>
#include <utility>
#include "graph.h"

class Network : private Graph {
private:
    std::vector<bool> is_up_;

    int K_;
    std::vector<int> terminals_;

public:

    Network(const Graph& G, std::vector<int> terminals);
    Network(int nodes, std::vector<int> terminals,
          std::vector< std::pair<int, int> > edge_list);

    int num_nodes() const;
    using Graph::num_edges;
    using Graph::print_graph;

    int get_diameter() const;
    int get_diameter(int level) const;

    int num_up() const;
    bool is_up(int edge_id) const;
    void set_state(int edge_id, bool is_up);

};

#endif
