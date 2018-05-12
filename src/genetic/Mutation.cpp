//
// Created by mario on 11/05/2018.
//

#include <time.h>
#include "Mutation.h"

Mutation::Mutation(double proba) : proba(proba) {}
Mutation::~Mutation(){
}

std::vector<Individu> Mutation::mutate(std::vector<Individu> &individus) const {
    srand(time(NULL));
    for (int i(0);i<individus.size();++i){
        std::vector<bool> id(individus[i].getId());
        for (int j(0);j<id.size();++j){
            double nombre = 0;
            nombre = (double) rand() / (double) RAND_MAX;
            if (nombre < proba){
                id[j] = !id[j];
            }
        }
        individus[i].setId(id);
    }
    return individus;
}