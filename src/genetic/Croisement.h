//
// Created by mario on 11/05/2018.
//

#ifndef PROJET_CROISEMENT_H
#define PROJET_CROISEMENT_H

#include "../Individu.h"

class Croisement{
private:
    int pos;
public:
    std::vector<Individu> croise(const std::vector<Individu> &parents) const ;
    Croisement(int pos);
    virtual ~Croisement();
};


#endif //PROJET_CROISEMENT_H
