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
        ind.setCout(f.calculeCout(ind, g, nT));
        tmp.push_back(ind);
    }
    for (int i(0);i<enfants.size();++i){
        Individu ind;
        ind.setId(enfants[i].getId());
        ind.setCout(f.calculeCout(ind, g, nT));
        tmp.push_back(ind);
    }
    for(Individu i: tmp){
        //std::cout << i.getCout() << std::endl;
    }
    /*
    Individu tampon;
    int v(0);
    while (v < tmp.size()){
        for (int i(0) ; i < tmp.size() ; ++i){
            if (tmp[i].getCout() < tmp[i+1].getCout()){
                tampon = tmp[i];
                tmp[i] = tmp[i+1];
                tmp[i+1] = tampon;
            }
        }
        v++;
    }*/
    std::sort(tmp.begin(), tmp.end(), sortIndividu);
    std::vector<Individu> res;
    for (int i(0);i<id.size();++i){
        res.push_back(tmp[i]);
    }
    return res;

}