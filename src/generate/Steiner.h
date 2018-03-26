//
// Created by Unuldur on 26/03/2018.
//

#ifndef PROJET_STEINER_H
#define PROJET_STEINER_H


#include "Generate.h"

class Steiner : public Generate{
public:
    Individu generate(const Graph *g, std::vector<Vertex> T, std::vector<Vertex> nT) const override;
};


#endif //PROJET_STEINER_H
