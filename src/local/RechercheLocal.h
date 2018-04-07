//
// Created by Unuldur on 25/03/2018.
//

#ifndef PROJET_RECHERCHELOCAL_H
#define PROJET_RECHERCHELOCAL_H


#include "../Graph.h"
#include "../Individu.h"
#include "Voisin.h"

class RechercheLocal {
private:
    Voisin * voisin;
public:
    virtual ~RechercheLocal();
    RechercheLocal(Voisin *voisin);
    Individu recherche(const Individu &individu, const Graph &g, const std::vector<Vertex> &T) const;
};


#endif //PROJET_RECHERCHELOCAL_H
