//
// Created by mario on 11/05/2018.
//

#ifndef PROJET_REMPLACEMENT_H
#define PROJET_REMPLACEMENT_H

#include "../Individu.h"
#include "../Fitness.h"

class Remplacement{
public:
    std::vector<Individu> remplace(const std::vector<Individu>& id, const std::vector<Individu>& enfants,
                                   const Fitness & f, const Graph & g, const std::vector<Vertex>& nT) const ;
};

#endif //PROJET_REMPLACEMENT_H
