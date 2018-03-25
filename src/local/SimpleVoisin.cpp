//
// Created by Unuldur on 25/03/2018.
//

#include <iostream>
#include "SimpleVoisin.h"
#include "../Fitness.h"

std::vector<Individu> SimpleVoisin::getVoisin(const Individu *individu, const Graph *graph, std::vector<Vertex> v) const {
    std::vector<Individu> voisin;
    int id = individu->getId();
    int b = 0x1;
    for (int j = v.size() - 1; j >= 0; --j) {
        voisin.emplace_back(id^b);
        b = b << 1;
    }

    std::vector<Individu> voisinOk;
    for (auto i : voisin) {
        int cout = fitness->calculeCout(&i, graph, v);
        if(cout < individu->getCout()){
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
