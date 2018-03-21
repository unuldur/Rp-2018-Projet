//
// Created by Unuldur on 21/03/2018.
//

#ifndef PROJET_GRAPH_H
#define PROJET_GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
using  namespace boost;
typedef adjacency_list<vecS, vecS, undirectedS, no_property, property <edge_weight_t, int>> Graph;
typedef graph_traits <Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;
typedef std::pair<int, int> E;
#endif //PROJET_GRAPH_H
