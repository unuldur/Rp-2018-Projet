//
// Created by Unuldur on 05/05/2018.
//

#ifndef PROJET_UTILS_H
#define PROJET_UTILS_H


#include "Graph.h"
#include "Individu.h"

class Utils {
public:
    static Graph copyGraph(const Individu & individu, const Graph & g, const std::vector<Vertex> & T);
    static int findWidth(const Graph& g,const  Vertex& d,const Vertex& d2);
    static void printGraph(Graph g, char* file);
};


#endif //PROJET_UTILS_H
