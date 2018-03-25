//
// Created by Unuldur on 21/03/2018.
//

#ifndef PROJET_FITNESS_H
#define PROJET_FITNESS_H


#include "Individu.h"
#include "Graph.h"

class Fitness {
public:
    virtual int calculeCout(const Individu *,const Graph *,std::vector<Vertex> ) const = 0;
};


#endif //PROJET_FITNESS_H
