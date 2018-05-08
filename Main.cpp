#include <iostream>

#include <fstream>
#include <chrono>
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
int main() {

    std::vector<int> terminaux;
    //test parser
    Graph g = Parser::readGraph("../resources/B/b07.stp", &terminaux);

    //Creation du graph
    /*
    const int num_nodes = 9;
    E edge_array[] = { E(0, 1), E(0, 2), E(0, 5), E(0, 7), E(1, 5),
                       E(1, 4), E(1, 8), E(2, 7), E(2, 6), E(2,3),
                       E(3, 6), E(4, 6), E(4, 8), E(5, 6)
    };
    int weights[] = { 8, 9, 2, 2, 2, 5, 8, 8, 4, 8, 3, 5, 8, 1};
    std::size_t num_edges = sizeof(edge_array) / sizeof(E);
    Graph g(edge_array, edge_array + num_edges, weights, num_nodes);
    terminaux.push_back(0);
    terminaux.push_back(4);
    terminaux.push_back(3);
    terminaux.push_back(2);
    terminaux.push_back(1);*/

    Fitness * f = new SimpleFitness();
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



    //Test voisin
    Voisin * v = new SimpleVoisin(f);

    //Steiner
    Steiner s;
    Individu stein = s.generate(g, T, nT);
    int val = f->calculeCout(stein, g, nT);
    stein.setCout(val);
    cout << "fitness steiner = " << val << endl;

    //Arbre couvrant min
    ArbreCouvrantMin acm;
    Individu acmi = acm.generate(g, T, nT);
    int valacmi = f->calculeCout(acmi, g, nT);
    acmi.setCout(valacmi);
    cout << "fitness arbre couvrant min = " << valacmi << endl;

    //Generate random;
    RandomiseGeneration rg(&s);
    Individu rstein = rg.generate(g, T, nT);
    int rval = f->calculeCout(rstein, g, nT);
    rstein.setCout(rval);
    cout << "fitness random steiner = " << rval << endl;

    //Simple individu

    Individu test(std::vector<bool>(nT.size(), true));
    int valtest = f->calculeCout(test, g, nT);
    test.setCout(valtest);
    cout << "fitness individu simple = " << valtest << endl;


    //Test recherche local
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    RechercheLocal l(v);
    Individu best = l.recherche(stein, g, nT);
    cout << "best :" << " cout = " << best.getCout() << endl;

    end = std::chrono::system_clock::now();

    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
            (end-start).count();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds << "s\n";

    return 0;
}