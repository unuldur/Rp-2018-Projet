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
        std::vector<Vertex> id(individu.getId());
        auto f = std::find(id.begin(), id.end(), nT[j]);
        if(f == id.end()){
            id.push_back(nT[j]);
        }else{
            id.erase(f);
        }
        voisin.emplace_back(id);
    }

    std::vector<Individu> voisinOk;
    for (auto i : voisin) {
        int cout = fitness->calculeCout(i, graph, nT);
        if(cout < individu.getCout()){
            i.setCout(cout);
            voisinOk.push_back(i);
        }
    }
    return voisinOk;
}

SimpleVoisin::SimpleVoisin(Fitness *fitness) : fitness(fitness) {}

SimpleVoisin::~SimpleVoisin() {
    delete fitness;
}
