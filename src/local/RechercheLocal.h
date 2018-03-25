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
    Individu recherche(const Individu *,const Graph *,std::vector<Vertex> ) const;
};


#endif //PROJET_RECHERCHELOCAL_H
