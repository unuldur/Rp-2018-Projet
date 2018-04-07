//
// Created by Unuldur on 26/03/2018.
//

#ifndef PROJET_GENERATE_H
#define PROJET_GENERATE_H


#include "../Individu.h"
#include "../Graph.h"

class Generate {
public:
    virtual Individu generate(const Graph &, const std::vector<Vertex> &T, const std::vector<Vertex> &nT) const = 0;
};


#endif //PROJET_GENERATE_H
