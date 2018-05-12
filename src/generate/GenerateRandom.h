//
// Created by mario on 12/05/2018.
//

#ifndef PROJET_GENERATERANDOM_H
#define PROJET_GENERATERANDOM_H


#include "Generate.h"

class GenerateRandom : public Generate{
private:
    double proba;
public:
    GenerateRandom(double proba);

public:
    Individu generate(const Graph &graph1, const std::vector<Vertex> &T, const std::vector<Vertex> &nT) const override;

};


#endif //PROJET_GENERATERANDOM_H
