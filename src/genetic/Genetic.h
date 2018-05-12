//
// Created by mario on 11/05/2018.
//

#ifndef PROJET_GENETIC_H
#define PROJET_GENETIC_H

#include "Generation.h"
#include "Croisement.h"
#include "Mutation.h"
#include "Remplacement.h"
#include "Selection.h"

class Genetic{
private:
    Generation * generation;
    Selection * selection;
    Croisement * croisement;
    Mutation * mutation;
    Remplacement * remplacement;
public:
    Individu algoGenetic(const Graph &g, const std::vector<Vertex> &T, const std::vector<Vertex> &nT, const int &nbIterations,
                                  const int &nbIndividus, const Fitness& f) const;
    Genetic(Generation * generation, Selection * selection, Croisement * croisement, Mutation * mutation, Remplacement * remplacement);
    virtual ~Genetic();
};

#endif //PROJET_GENETIC_H
