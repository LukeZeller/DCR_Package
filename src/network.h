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

class Network {
private:
    Graph G_;
    std::vector<bool> is_up_;

    int K_;
    std::vector<int> terminals_;

public:

    Network(int nodes, int num_terminals, std::vector<int> terminals,
          std::vector< std::pair<int, int> > edge_list);

    int get_diameter() const;
    int get_diameter(int level) const;
    
    int get_nodes() const;
    int get_edges() const;
    bool is_up(int edge_id) const;
    int get_num_up() const;
    void set_state(int edge_id, bool is_up);

};

#endif
