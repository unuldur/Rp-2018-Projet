//
// Created by Unuldur on 25/03/2018.
//

#include <iostream>
#include "SimpleVoisin.h"
#include "../Fitness.h"

std::vector<Individu> SimpleVoisin::getVoisin(const Individu &individu, const Graph &graph,
                                              const std::vector<Vertex> &nT) const {
    std::vector<Individu> voisin;
    for (int j = nT.size() - 1; j >= 0; --j) {
        std::vector<bool> id(individu.getId());
        if(!id[j]){
            int conn = 0;
            for(std::pair<graph_traits<Graph>::in_edge_iterator,graph_traits<Graph>::in_edge_iterator> p = boost::in_edges(nT[j], graph);
                    p.first != p.second ; p.first++){
                Vertex sou = source(*(p.first), graph);
                int pos = std::find(nT.begin(), nT.end(), sou) - nT.begin();
                if(pos < nT.size() && id[pos]){
                    conn ++;
                }
            }
            if(conn <= 1){
                continue;
            }
        }
        id[j] = !id[j];
        voisin.emplace_back(id);
    }

    std::vector<Individu> voisinOk;
    int inc = 0;
    int vs = voisin.size();
    for (auto i : voisin) {
        std::cout << inc << "/" << vs << std::endl;
        int cout = fitness->calculeCout(i, graph, nT);
        if(cout < individu.getCout()){
            i.setCout(cout);
            voisinOk.push_back(i);
        }
        inc++;
    }
    return voisinOk;
}

SimpleVoisin::SimpleVoisin(Fitness *fitness) : fitness(fitness) {}

SimpleVoisin::~SimpleVoisin() {
    delete fitness;
}
