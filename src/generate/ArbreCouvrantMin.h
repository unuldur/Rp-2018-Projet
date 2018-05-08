//
// Created by Unuldur on 08/05/2018.
//

#ifndef PROJET_ARBRECOUVRANTMIN_H
#define PROJET_ARBRECOUVRANTMIN_H


#include "Generate.h"

class ArbreCouvrantMin : public Generate{
public:
    Individu generate(const Graph &graph1, const std::vector<Vertex> &T, const std::vector<Vertex> &nT) const override;

};


#endif //PROJET_ARBRECOUVRANTMIN_H
