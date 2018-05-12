//
// Created by mario on 11/05/2018.
//

#ifndef PROJET_GENERATION_H
#define PROJET_GENERATION_H

#include "../Individu.h"
#include "../generate/Generate.h"

class Generation{
private:
    Generate * generate;
public:
    Generation(Generate *generate);

public:
    std::vector<Individu> genere(const Graph & g, const std::vector<Vertex> &T, const std::vector<Vertex> &nT, int nbIndividus) const ;
    virtual ~Generation();
};

#endif //PROJET_GENERATION_H
