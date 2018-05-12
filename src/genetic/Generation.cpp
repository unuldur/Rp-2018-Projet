//
// Created by mario on 11/05/2018.
//

#include <time.h>
#include <iostream>
#include "Generation.h"

std::vector<Individu> Generation::genere(const Graph & g, const std::vector<Vertex> &T, const std::vector<Vertex> &nT, int nbIndividus) const {
    std::vector<Individu> individus;
    for (int i(0); i<nbIndividus; ++i){
        individus.emplace_back(generate->generate(g, T, nT));
    }
    return individus;
}

Generation::~Generation() {
}

Generation::Generation(Generate *generate) :generate(generate) {}
