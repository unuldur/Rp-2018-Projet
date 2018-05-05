//
// Created by Unuldur on 05/05/2018.
//

#include "Utils.h"
#include <iostream>
#include <fstream>
#include <boost/graph/copy.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/make_connected.hpp>
#include <map>

using namespace boost;
int Utils::findWidth(Graph g, Vertex d, Vertex d2){
    graph_traits<Graph>::edge_iterator eiter, eiter_end;
    for (boost::tie(eiter, eiter_end) = edges(g); eiter != eiter_end; ++eiter) {
        if(source(*eiter, g) == d && target(*eiter, g) == d2){
            return get(edge_weight, g, *eiter);
        }
        if(source(*eiter, g) == d2 && target(*eiter, g) == d){
            return get(edge_weight, g, *eiter);
        }
    }
}

Graph Utils::copyGraph(const Individu &individu, const Graph &g, const std::vector<Vertex> &T) {
    graph_traits<Graph>::edge_iterator eiter, eiter_end;
    std::vector<int> weights;
    std::vector<E> edges;
    std::set<Vertex> sommets;
    std::set<Vertex> sommetsAfter;
    std::map <Vertex, int> sommetsm;
    std::vector<Vertex> id = individu.getId();
    int ids = 0;
    for (boost::tie(eiter, eiter_end) = boost::edges(g); eiter != eiter_end; ++eiter) {
        Vertex s = source(*eiter, g);
        Vertex t = target(*eiter, g);
        unsigned long pos_deb = std::find(T.begin(), T.end(), s) - T.begin();
        unsigned long pos_end = std::find(T.begin(), T.end(), t) - T.begin();
        bool dep = true;
        bool arr = true;
        if(pos_deb < T.size() && std::find(id.begin(), id.end(), s) == id.end()){
            dep = false;
        }
        if(pos_end < T.size() && std::find(id.begin(), id.end(), t) == id.end()){
            arr = false;
        }
        if(dep && !arr){
            if(std::find(sommets.begin(), sommets.end(), s) == sommets.end()){
                sommetsm[s] = ids;
                ids++;
            }
            edges.emplace_back(sommetsm[s], sommetsm[s]);
            weights.emplace_back(0);
            sommets.insert(s);
        }
        if(!dep && arr){
            if(std::find(sommets.begin(), sommets.end(), t) == sommets.end()){
                sommetsm[t] = ids;
                ids++;
            }
            edges.emplace_back(sommetsm[t], sommetsm[t]);
            weights.emplace_back(0);
            sommets.insert(t);
        }
        if(dep && arr){
            if(std::find(sommets.begin(), sommets.end(), s) == sommets.end()){
                sommetsm[s] = ids;
                ids++;
            }
            if(std::find(sommets.begin(), sommets.end(), t) == sommets.end()){
                sommetsm[t] = ids;
                ids++;
            }
            edges.emplace_back(sommetsm[s], sommetsm[t]);
            weights.emplace_back(findWidth(g, s, t));
            sommets.insert(s);
            sommets.insert(t);
        }
    }

    return Graph(&edges[0], &edges[0] + edges.size(), &weights[0], sommets.size());
}
