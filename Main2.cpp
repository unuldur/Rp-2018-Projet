//
// Created by Unuldur on 08/05/2018.
//

#include <iostream>

#include <fstream>
#include <chrono>
#include <string.h>
#include "src/Graph.h"
#include "src/Fitness.h"
#include "src/SimpleFitness.h"
#include "src/local/SimpleVoisin.h"
#include "src/local/Voisin.h"
#include "src/local/RechercheLocal.h"
#include "src/generate/Steiner.h"
#include "src/parser/Parser.h"
#include "src/generate/ArbreCouvrantMin.h"
#include "src/generate/RandomiseGeneration.h"

using namespace std;
int main2() {


    string names[20] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
    Fitness * f = new SimpleFitness();
    Voisin * v = new SimpleVoisin(f);
    RechercheLocal l(v);
    Steiner s;

    for(string name : names) {
        std::vector<int> terminaux;
        Graph g = Parser::readGraph("../resources/C/c"+name+".stp", &terminaux);

        std::vector<Vertex> nT;
        std::vector<Vertex> T;

        //Creation de non(nT)
        typedef property_map<Graph, vertex_index_t>::type IndexMap;
        IndexMap index = get(vertex_index, g);

        typedef graph_traits<Graph>::vertex_iterator vertex_iter;
        std::pair<vertex_iter, vertex_iter> vp;
        for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
            Vertex v = *vp.first;
            if(std::find(terminaux.begin(), terminaux.end(), index[v]) == terminaux.end())
            {
                nT.push_back(v);
            }else{
                T.push_back(v);
            }
        }

        Individu stein = s.generate(g, T, nT);
        int val = f->calculeCout(stein, g, nT);
        stein.setCout(val);
        cout << "fitness steiner = " << val << endl;


        //Test recherche local
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        Individu best = l.recherche(stein, g, nT);
        cout << "best :" << " cout = " << best.getCout() << endl;

        end = std::chrono::system_clock::now();

        int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
                (end - start).count();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "b" << name << ".stp\nfinished computation at " << std::ctime(&end_time)
                  << "elapsed time: " << elapsed_seconds << "s\n";
    }

    return 0;
}