//
// Created by Unuldur on 08/05/2018.
//

#include <boost/graph/copy.hpp>
#include "RandomiseGeneration.h"
#include "../Utils.h"

Individu RandomiseGeneration::generate(const Graph &graph, const std::vector<Vertex> &T, const std::vector<Vertex> &nT) const {
    Graph g;
    copy_graph(graph, g);
    auto weights = get(edge_weight, g);
    boost::graph_traits< Graph >::edge_iterator e_it, e_end;
    for(std::tie(e_it, e_end) = boost::edges(g); e_it != e_end; ++e_it)
    {
        int randChang = rand() % 15 + 5;
        if(rand() % 2 == 0){
            randChang = - randChang;
        }
        weights[*e_it] += weights[*e_it] * randChang / 100;
    }
    return gen->generate(g, T, nT);
}

RandomiseGeneration::RandomiseGeneration(Generate *g) : gen(g) {}
