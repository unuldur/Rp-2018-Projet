//
// Created by mario on 11/05/2018.
//

#include <time.h>
#include <iostream>
#include "Selection.h"

std::vector<Individu> Selection::select(const std::vector<Individu>& id) const {

    srand(time(0));
    int sumFitness = 0;
    for(Individu i: id){
        sumFitness += i.getCout();
    }
    int pos1 = randOne(id, sumFitness);
    int pos2 = randOne(id, sumFitness);
    while (pos1 == pos2){
        pos2 = randOne(id, sumFitness);
    }
    std::vector<Individu> parents;
    parents.push_back(id[pos1]);
    parents.push_back(id[pos2]);
    return parents;
}

unsigned int Selection::randOne(const std::vector<Individu> &id, int sumFitness) const {
    return rand() % id.size();
}
