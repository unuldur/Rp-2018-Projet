//
// Created by Unuldur on 25/03/2018.
//

#include <iostream>
#include "SimpleVoisin.h"
#include "../Fitness.h"
#include "../thread/mingw.thread.h"

void calcFitness(Individu * i, int coutMax,const Graph& graph, const std::vector<Vertex>& nT, std::vector<Individu> *voisins, Fitness * fitness) {
    int cout = fitness->calculeCout(*i, graph, nT);
    if(cout < coutMax){
        i->setCout(cout);
        voisins->push_back(*i);
    }
}

std::vector<Individu> SimpleVoisin::getVoisin(const Individu &individu, const Graph &graph,
                                              const std::vector<Vertex> &nT) const {
    std::vector<Individu> voisin;
    for (int j = 0; j < nT.size(); ++j) {
        std::vector<bool> id(individu.getId());
        if(!id[j]){
            int conn = 0;
            for(std::pair<graph_traits<Graph>::in_edge_iterator,graph_traits<Graph>::in_edge_iterator> p = boost::in_edges(nT[j], graph);
                    p.first != p.second ; p.first++){
                Vertex sou = source(*(p.first), graph);
                unsigned int pos = std::find(nT.begin(), nT.end(), sou) - nT.begin();
                if(pos < nT.size() && id[pos]){
                    conn ++;
                }else{
                    if(pos >= nT.size()){
                        conn ++;
                    }
                }
            }
            if(conn <= 1){
                continue;
            }
        }
        id[j] = !id[j];
        voisin.emplace_back(id);
    }
    std::vector<Individu> voisinOk;
    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < voisin.size(); ++i) {
        threads.emplace_back(calcFitness, &(voisin[i]), individu.getCout(), graph, nT, &voisinOk, fitness);
    }
    for (unsigned int i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
    return voisinOk;
}

SimpleVoisin::SimpleVoisin(Fitness *fitness) : fitness(fitness) {}

SimpleVoisin::~SimpleVoisin() {
}


/*Individu * i, int coutMax, const Graph &graph, const std::vector<Vertex> &nT,
                               std::vector<Individu> *voisins*/

