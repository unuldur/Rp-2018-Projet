//
// Created by Unuldur on 07/04/2018.
//

#include "Parser.h"
#include <iostream>
#include <fstream>

using namespace std;
Graph Parser::readGraph(const std::string &file, std::vector<int> *T) {
    std::ifstream fichier(file, std::ios::in);
    std::string line;
    int section = 0;
    int nbVertex = 0;
    vector<E> edges;
    vector<int> weights;
    while (std::getline(fichier, line))
    {
        if(line == "END"){
            section = 0;
            continue;
        }
        switch (section){
            case 1: {
                size_t vertex_count = line.find("Nodes");
                size_t edge = line.find("E ");
                if (vertex_count != string::npos) {
                    string nbvert = line.substr(6, line.size());
                    nbVertex = stoi(nbvert);
                }
                if (edge != string::npos) {
                    istringstream iss(line);
                    string mot;
                    int i = 0;
                    int dep = 0;
                    int arr = 0;
                    int weigth = 0;
                    while (std::getline(iss, mot, ' ')) {
                        switch (i) {
                            case 1:
                                dep = stoi(mot);
                                break;
                            case 2:
                                arr = stoi(mot);
                                break;
                            case 3:
                                weigth = stoi(mot);
                                break;
                        }
                        ++i;
                    }
                    edges.emplace_back(dep - 1, arr - 1);
                    weights.push_back(weigth);
                }
                break;
            }
            case 2: {
                size_t term = line.find("T ");
                if (term != string::npos) {
                    string ta = line.substr(2, line.size());
                    T->push_back(stoi(ta) - 1);
                }
                break;
            }
        }
        size_t z = line.find("SECTION");
        if(z != string::npos){
            string sec = line.substr(8, line.size());
            if(sec == "Graph"){
                section = 1;
            }
            if(sec == "Terminals"){
                section = 2;
            }
        }
    }

    return Graph(&edges[0], &edges[0] + edges.size(), &weights[0], nbVertex);
}
