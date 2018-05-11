//
// Created by Unuldur on 25/03/2018.
//

#include <iostream>
#include <chrono>
#include "RechercheLocal.h"

Individu RechercheLocal::recherche(const Individu &premier, const Graph &g, const std::vector<Vertex> &T) const {
    Individu best = premier;
    std::vector<Individu> v = voisin->getVoisin(best, g, T);
    int size = v.size();
    while(size > 0){
        int randomIndex = rand() % size;
        best = v[randomIndex];
        //std::cout << "New best : id="  << " cout=" <<best.getCout() << std::endl;
        v = voisin->getVoisin(best, g, T);
        size = v.size();
    }
    return best;
}

RechercheLocal::RechercheLocal(Voisin *voisin) : voisin(voisin) {}

RechercheLocal::~RechercheLocal() {
    delete voisin;
}

Individu RechercheLocal::recherche(const Generate &generate, const Graph &g, const std::vector<Vertex> &T,
                                   const std::vector<Vertex> &nT, const Fitness &f, int timer) const {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    long long int elapsed_seconds = 0;
    Individu best;
    do{
        Individu i = generate.generate(g, T, nT);
        i.setCout(f.calculeCout(i, g, nT));
        Individu ir = recherche(i, g, nT);
        end = std::chrono::system_clock::now();
        elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
        if(ir.getCout() < best.getCout()){
            best = ir;
            std::cout << "New best of best: cout=" <<best.getCout() << std::endl;

        }
        //std::cout << "elapsed_second =" <<elapsed_seconds << std::endl;
    }while(elapsed_seconds < timer);
    return best;
}
