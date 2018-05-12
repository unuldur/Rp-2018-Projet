//
// Created by mario on 11/05/2018.
//

#include <iostream>
#include "Remplacement.h"
#include "../thread/mingw.thread.h"

bool sortIndividu(Individu i1, Individu i2){
    return i1.getCout() < i2.getCout();
}

std::vector<Individu> Remplacement::remplace(const std::vector<Individu>& id, const std::vector<Individu>& enfants,
                                             const Fitness & f, const Graph & g, const std::vector<Vertex>& nT) const{
    std::vector<Individu> tmp;

    for (int i(0);i<id.size();++i){
        Individu ind;
        ind.setId(id[i].getId());
        ind.setCout(id[i].getCout());
        tmp.push_back(ind);
    }
    for (int i(0);i<enfants.size();++i){
        Individu ind;
        ind.setId(enfants[i].getId());
        ind.setCout(id[i].getCout());
        tmp.push_back(ind);
    }
    std::sort(tmp.begin(), tmp.end(), sortIndividu);
    std::vector<Individu> res;
    for (int i(0);i<id.size();++i){
        res.push_back(tmp[i]);
    }
    return res;

}