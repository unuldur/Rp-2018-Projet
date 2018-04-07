//
// Created by Unuldur on 25/03/2018.
//

#include <iostream>
#include "RechercheLocal.h"

Individu RechercheLocal::recherche(const Individu &premier, const Graph &g, const std::vector<Vertex> &T) const {
    Individu best = premier;
    std::vector<Individu> v = voisin->getVoisin(best, g, T);
    int size = v.size();
    while(size > 0){
        int randomIndex = rand() % size;
        best = v[randomIndex];
        std::cout << "New best : id=" << best.getId() << " cout=" <<best.getCout() << std::endl;
        v = voisin->getVoisin(best, g, T);
        size = v.size();
    }
    return best;
}

RechercheLocal::RechercheLocal(Voisin *voisin) : voisin(voisin) {}

RechercheLocal::~RechercheLocal() {
    delete voisin;
}
