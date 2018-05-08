//
// Created by Unuldur on 08/05/2018.
//

#include <iostream>
#include "ArbreCouvrantMin.h"

Individu ArbreCouvrantMin::generate(const Graph &graph, const std::vector<Vertex> &T, const std::vector<Vertex> &nT) const {
    std::vector<bool> id(nT.size(), true);
    std::vector<Edge> spanning_tree;
    kruskal_minimum_spanning_tree(graph, std::back_inserter(spanning_tree));
    bool mod = true;
    while(mod) {
        mod = false;
        std::set<Vertex> vertexs;
        std::set<Vertex> nF;
        for (Edge e : spanning_tree) {
            Vertex s = source(e, graph);
            Vertex t = target(e, graph);
            unsigned int poss = std::find(nT.begin(), nT.end(), s) - nT.begin();
            unsigned int post = std::find(nT.begin(), nT.end(), t) - nT.begin();
            if (poss < nT.size() && !id[poss]) {
                continue;
            }
            if (post < nT.size() && !id[post]) {
                continue;
            }
            if (!vertexs.insert(s).second) {
                nF.insert(s);
            }
            if (!vertexs.insert(t).second) {
                nF.insert(t);
            }
        }
        for (unsigned int j = 0; j < nT.size(); j++) {
            if (id[j] && std::find(nF.begin(), nF.end(), nT[j]) == nF.end()) {
                id[j] = false;
                mod = true;
            }
        }
    }
    return Individu(id);
}
