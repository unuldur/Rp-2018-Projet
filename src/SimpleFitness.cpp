//
// Created by Unuldur on 21/03/2018.
//

#include <iostream>
#include <fstream>
#include "SimpleFitness.h"
#include <boost/graph/copy.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/make_connected.hpp>

using namespace boost;


static void printGraph(Graph g, char* file){
    std::ofstream fout(file);
    fout << "graph A {\n"
         << " rankdir=LR\n"
         << " size=\"3,3\"\n"
         << " ratio=\"filled\"\n"
         << " edge[style=\"bold\"]\n" << " node[shape=\"circle\"]\n";
    graph_traits<Graph>::edge_iterator eiter, eiter_end;
    for (boost::tie(eiter, eiter_end) = edges(g); eiter != eiter_end; ++eiter) {
        fout << source(*eiter, g) << " -- " << target(*eiter, g);
        fout << "[color=\"black\", label=\"" << get(edge_weight, g, *eiter) << "\"];\n";
    }
    fout << "}\n";
}

int SimpleFitness::calculeCout(const Individu & individu, const Graph & completeGraph, const std::vector<Vertex> & T) const {
    Graph g;
    copy_graph(completeGraph, g);
    unsigned long id = individu.getId();
    for (int j = T.size() - 1; j >= 0; --j) {
        unsigned long b = id & 1;
        if(b == 0){
            clear_vertex(T[j], g);
            remove_vertex(T[j], g);
        }
        id = id >> 1;
    }

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
