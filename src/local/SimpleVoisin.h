//
// Created by Unuldur on 25/03/2018.
//

#ifndef PROJET_SIMPLEVOISIN_H
#define PROJET_SIMPLEVOISIN_H


#include "Voisin.h"
#include "../Fitness.h"

class SimpleVoisin : public Voisin{
public:


private:
    Fitness * fitness;
public:
    virtual ~SimpleVoisin();
    SimpleVoisin(Fitness *fitness);
    std::vector<Individu> getVoisin(const Individu *individu, const Graph *graph1, std::vector<Vertex> vector) const override;
};


#endif //PROJET_SIMPLEVOISIN_H
