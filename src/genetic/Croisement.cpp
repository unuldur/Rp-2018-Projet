//
// Created by mario on 11/05/2018.
//

#include "Croisement.h"
std::vector<Individu> Croisement::croise(const std::vector<Individu> &parents) const {
    std::vector<bool> e1;
    std::vector<bool> e2;
    std::vector<bool> p1(parents[0].getId());
    std::vector<bool> p2(parents[1].getId());
    for (int i(0); i<pos; ++i){
        e1.push_back(p1[i]);
        e2.push_back(p2[i]);
    }
    for (int i(pos); i<p1.size(); ++i){
        e1.push_back(p2[i]);
        e2.push_back(p1[i]);
    }
    std::vector<Individu> enfant;
    enfant.emplace_back(e1);
    enfant.emplace_back(e2);
    return enfant;
}

Croisement::Croisement(int pos) : pos(pos){}

Croisement::~Croisement(){
}