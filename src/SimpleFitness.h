//
// Created by Unuldur on 21/03/2018.
//

#ifndef PROJET_SIMPLEFITNESS_H
#define PROJET_SIMPLEFITNESS_H


#include "Fitness.h"

class SimpleFitness : Fitness{
public:
    static const int M = 1000000000;
    int calculeCout(const Individu *,Graph &, std::vector<Vertex> ) const override;
};


#endif //PROJET_SIMPLEFITNESS_H
