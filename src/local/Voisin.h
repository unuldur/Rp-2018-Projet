//
// Created by Unuldur on 25/03/2018.
//

#ifndef PROJET_VOISIN_H
#define PROJET_VOISIN_H

#include <vector>
#include "../Individu.h"
#include "../Graph.h"

class Voisin {
public:
    virtual std::vector<Individu> getVoisin(const Individu *,const Graph *,std::vector<Vertex> ) const = 0;
};
#endif //PROJET_VOISIN_H
