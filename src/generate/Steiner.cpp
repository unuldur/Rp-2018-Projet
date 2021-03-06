//
// Created by Unuldur on 26/03/2018.
//

#include "Steiner.h"
#include "../Utils.h"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>
#include <fstream>
#include <iostream>

using namespace boost;

Individu Steiner::generate(const Graph &g, const std::vector<Vertex> &T, const std::vector<Vertex> &nT) const {
    //Construction G1
    const int n = T.size();
    std::vector<E> edges;
    std::vector<int> weights;
    std::map<Vertex, std::vector<Vertex>> parents;
    for (int j = 0; j < n; ++j) {
        std::vector<Vertex > p(num_vertices(g));
        std::vector<int> d(num_vertices(g));
        Vertex s = vertex(T[j], g);
        dijkstra_shortest_paths(g, s,
                                predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));
        parents[s] = p;
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
    auto weh = get(edge_weight, g);
    for(Edge e: g2){
        Vertex src = source(e, g1);
        std::vector<Vertex> p = parents[src];
        Vertex tmp = target(e, g1);
        do{
            if(std::find(edgesG3.begin(), edgesG3.end(), E(p[tmp], tmp)) == edgesG3.end()){
                edgesG3.emplace_back(p[tmp], tmp);
                weightsG3.push_back(Utils::findWidth(g, p[tmp], tmp));
                sommets.insert(tmp);
                sommets.insert(p[tmp]);
            }
            tmp = p[tmp];
        }while(tmp != src);
    }
    Graph g3(&edgesG3[0], &edgesG3[0] + edgesG3.size(), &weightsG3[0], sommets.size());
    Utils::printGraph(g3, "steinerG3.dot");
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
    unsigned int nTSize = nT.size();
    std::vector<bool> id(nTSize, false);
    for(Vertex v: nleaf){
        int pos = std::find(nT.begin(), nT.end(), v) - nT.begin();
        if(pos < nTSize){
            id[pos] = true;
        }
    }
    return Individu(id);
}

