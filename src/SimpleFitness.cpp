//
// Created by Unuldur on 21/03/2018.
//

#include <iostream>
#include <fstream>
#include "SimpleFitness.h"
#include "Utils.h"
#include <boost/graph/copy.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/make_connected.hpp>

using namespace boost;

int SimpleFitness::calculeCout(const Individu & individu, const Graph & completeGraph, const std::vector<Vertex> & T) const {
    Graph g = Utils::copyGraph(individu, completeGraph, T);

    Utils::printGraph(g, "test.dot");
    Utils::printGraph(completeGraph, "test2.dot");


    bool connected = true;
    std::vector<graph_traits<Graph>::vertices_size_type> component(num_vertices(g));
    if(connected_components(g, &component[0]) > 1){
        connected = false;
    };


    std::vector<Edge> spanning_tree;
    kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));

    int fitness = 0;
    int edges_number = 0;
    int vertice_number = 0;

    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
        vertice_number++;
    }

    graph_traits<Graph>::edge_iterator eiter, eiter_end;
    for (boost::tie(eiter, eiter_end) = edges(g); eiter != eiter_end; ++eiter) {
        if (std::find(spanning_tree.begin(), spanning_tree.end(), *eiter) != spanning_tree.end()){
            fitness += get(edge_weight, g, *eiter);
            ++edges_number;
        }

    }

    if(connected) {
        return fitness;
    }
    else {
        return fitness + M * (vertice_number - 1 - edges_number);
    }
}
