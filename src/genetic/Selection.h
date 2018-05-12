//
// Created by mario on 11/05/2018.
//

#ifndef PROJET_SELECTION_H
#define PROJET_SELECTION_H

#include "../Individu.h"

class Selection{
private:
    unsigned int randOne(const std::vector<Individu>& id, int sumFitness)const ;
public:
    std::vector<Individu> select(const std::vector<Individu>& id) const ;
};
#endif //PROJET_SELECTION_H
