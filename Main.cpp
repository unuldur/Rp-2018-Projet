#include <iostream>

#include <fstream>
#include "src/Graph.h"
#include "src/Fitness.h"
#include "src/SimpleFitness.h"
#include "src/local/SimpleVoisin.h"
#include "src/local/Voisin.h"
#include "src/local/RechercheLocal.h"
#include "src/generate/Steiner.h"
#include "src/parser/Parser.h"

using namespace std;
int main() {

    std::vector<int> terminaux;
    //test parser
    Graph g = Parser::readGraph("../resources/B/b01.stp", &terminaux);

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
    Individu p(0);
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

    //Calcule du cout de l'individu premier
    int val = f->calculeCout(stein, g, nT);
    stein.setCout(val);
    cout << "fitness = " << val << endl;

    //Test recherche local
    RechercheLocal l(v);
    Individu best = l.recherche(stein, g, nT);
    cout << "best : id = " << best.getId() << " cout = " << best.getCout() << endl;

    return 0;
}