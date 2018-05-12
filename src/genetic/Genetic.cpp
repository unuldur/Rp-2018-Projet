//
// Created by mario on 11/05/2018.
//

#include "Genetic.h"
#include <iostream>
#include "../thread/mingw.thread.h"

void calcFitness1(Individu * i, const Graph& graph, const std::vector<Vertex>& nT,const Fitness & fitness) {
    i->setCout(fitness.calculeCout(*i, graph, nT));
}

Individu Genetic::algoGenetic(const Graph &g, const std::vector<Vertex> &T, const std::vector<Vertex> &nT, const int &nbIterations,
                              const int &nbIndividus, const Fitness& f) const{
    std::vector<Individu> id(generation->genere(g, T, nT, nbIndividus));
    std::vector<std::thread> ts;
    for(Individu i:id){
        ts.emplace_back(calcFitness1, &i, g, nT, f);
    }
    for (int k = 0; k < ts.size(); ++k) {
        ts[k].join();
    }
    for (int i(0) ; i < nbIterations ; ++i){
        std::vector<Individu> enfants;
        for (int j = 0 ; j < nbIndividus / 2 ; ++j){
            std::vector<Individu> parents(selection->select(id));
            std::vector<Individu> enfant(croisement->croise(parents));
            for (int it(0); it<enfant.size();++it){
                enfants.push_back(enfant[it]);
            }
        mutation->mutate(enfants);
        id = remplacement->remplace(id, enfants,f ,g, nT);
        }
        std::cout << i << " ";
    }
    return id[0];
}


Genetic::~Genetic() {
    delete generation;
    delete selection;
    delete croisement;
    delete mutation;
    delete remplacement;
}

Genetic::Genetic(Generation *generation, Selection *selection, Croisement *croisement, Mutation *mutation,
                 Remplacement *remplacement): generation(generation), selection(selection), croisement(croisement), mutation(mutation), remplacement(remplacement){

}
