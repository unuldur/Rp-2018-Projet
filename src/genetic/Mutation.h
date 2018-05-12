//
// Created by mario on 11/05/2018.
//

#ifndef PROJET_MUTATION_H
#define PROJET_MUTATION_H

#include "../Individu.h"

class Mutation{
private:
    double proba;
public:
    std::vector<Individu> mutate(std::vector<Individu> & id) const ;
    Mutation(double proba);
    virtual ~Mutation();
};


#endif //PROJET_MUTATION_H
