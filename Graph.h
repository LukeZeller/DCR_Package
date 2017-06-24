/**
   @file Graph.h
   @author Luke Zeller
   
   Definition of member functions and variables for
   class Graph
*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <utility>

struct Edge {
    int v0, v1;
    bool is_up;

    Edge(int v0, int v1);
    int other(int v);    
};

class Graph {
private:
    int N_, K_;
    std::vector<int> terminals_;
    std::vector<Edge> edges_;
    std::vector< std::vector<int> > incident_id_list_;
    
public:

    Graph(int nodes, int num_terminals, std::vector<int> terminals,
          std::vector< std::pair<int, int> > edge_list);

    int get_diameter();
    int get_diameter(int level);
    
    int get_nodes();
    int get_edges();
    bool is_up(int edge_id);
    int get_num_up();
    void set_state(int edge_id, bool is_up);

};

#endif
