//
// Created by mario on 12/05/2018.
//

#include <time.h>
#include "GenerateRandom.h"

Individu
GenerateRandom::generate(const Graph &graph1, const std::vector<Vertex> &T, const std::vector<Vertex> &nT) const {
    srand(time(NULL));
    std::vector<bool> id;
    for (int j(0); j<nT.size(); ++j) {
        double nombre = 0;
        nombre = (double) rand() / RAND_MAX;
        id.push_back(nombre < proba);
    }
    return Individu(id);
}

GenerateRandom::GenerateRandom(double proba) : proba(proba) {}
