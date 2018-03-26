//
// Created by Unuldur on 26/03/2018.
//

#include "Steiner.h"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>
#include <fstream>
#include <iostream>

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

int findWidth(Graph g, Vertex d, Vertex d2){
    graph_traits<Graph>::edge_iterator eiter, eiter_end;
    for (boost::tie(eiter, eiter_end) = edges(g); eiter != eiter_end; ++eiter) {
        if(source(*eiter, g) == d && target(*eiter, g) == d2){
            return get(edge_weight, g, *eiter);
        }
        if(source(*eiter, g) == d2 && target(*eiter, g) == d){
            return get(edge_weight, g, *eiter);
        }
    }
}

Individu Steiner::generate(const Graph *g, std::vector<Vertex> T, std::vector<Vertex> nT) const {
    //Construction G1
    const int n = T.size();
    std::vector<E> edges;
    std::vector<int> weights;
    std::vector<std::vector<Vertex>> parents;
    for (int j = 0; j < n; ++j) {
        std::vector<Vertex > p(num_vertices(*g));
        std::vector<int> d(num_vertices(*g));
        Vertex s = vertex(T[j], *g);
        dijkstra_shortest_paths(*g, s,
                                predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, *g))).distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, *g))));
        parents.push_back(p);
        for (int k = j; k < n; ++k) {
            if (j == k) continue;
            edges.emplace_back(T[j], T[k]);
            weights.push_back(d[T[k]]);
        }
    }
    std::size_t num_edges = edges.size();
    Graph g1(&edges[0], &edges[0] + num_edges, &weights[0], n);

    //Construction g2
    std::vector<Edge> g2;
    kruskal_minimum_spanning_tree(g1, std::back_inserter(g2));

    //Construction g3
    std::vector<int> weightsG3;
    std::vector<E> edgesG3;
    std::set<Vertex> sommets;
    auto weh = get(edge_weight, *g);
    for(Edge e: g2){
        Vertex src = source(e, g1);
        std::vector<Vertex> p = parents[src];
        Vertex tmp = target(e, g1);
        do{
            if(std::find(edgesG3.begin(), edgesG3.end(), E(p[tmp], tmp)) == edgesG3.end()){
                edgesG3.emplace_back(p[tmp], tmp);
                weightsG3.push_back(findWidth(*g, p[tmp], tmp));
                sommets.insert(tmp);
                sommets.insert(p[tmp]);
            }
            tmp = p[tmp];
        }while(tmp != src);
    }
    Graph g3(&edgesG3[0], &edgesG3[0] + edgesG3.size(), &weightsG3[0], sommets.size());

    //Construction g4
    std::vector<Edge> g4;
    kruskal_minimum_spanning_tree(g3, std::back_inserter(g4));

    //Construction g5
    std::set<Vertex> ver;
    std::set<Vertex> nleaf;
    for(Edge e: g4) {
        auto p = ver.insert(source(e, g3));
        auto p2 = ver.insert(target(e, g3));
        if(!p.second){
            nleaf.insert(source(e, g3));
        }
        if(!p2.second){
            nleaf.insert(target(e, g3));
        }
    }
    int id = 0;
    int nTSize = nT.size();
    for(Vertex v: nleaf){
        if(std::find(nT.begin(), nT.end(), v) != nT.end()){
            int b = int(v - n);
            b = nTSize - b - 1;
            id = id | (0x1 << b);
        }
    }
    return Individu(id);
}

