//
// Created by Unuldur on 08/05/2018.
//

#ifndef PROJET_RANDOMISEGENERATION_H
#define PROJET_RANDOMISEGENERATION_H


#include "Generate.h"

class RandomiseGeneration : public Generate{
private:
    Generate * gen;
public:
    RandomiseGeneration(Generate *g);

public:
    Individu generate(const Graph &graph1, const std::vector<Vertex> &T, const std::vector<Vertex> &nT) const override;

};


#endif //PROJET_RANDOMISEGENERATION_H
