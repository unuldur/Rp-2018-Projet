#include <iostream>

#include <fstream>
#include "src/Graph.h"
#include "src/Fitness.h"
#include "src/SimpleFitness.h"
#include "src/local/SimpleVoisin.h"
#include "src/local/Voisin.h"
#include "src/local/RechercheLocal.h"
#include "src/generate/Steiner.h"

using namespace std;
int main() {

    //Creation du graph
    const int num_nodes = 9;
    E edge_array[] = { E(0, 1), E(0, 2), E(0, 5), E(0, 7), E(1, 5),
                       E(1, 4), E(1, 8), E(2, 7), E(2, 6), E(2,3),
                       E(3, 6), E(4, 6), E(4, 8), E(5, 6)
    };
    int weights[] = { 8, 9, 2, 2, 2, 5, 8, 8, 4, 8, 3, 5, 8, 1};
    std::size_t num_edges = sizeof(edge_array) / sizeof(E);
    Graph g(edge_array, edge_array + num_edges, weights, num_nodes);

    Fitness * f = new SimpleFitness();
    Individu p(0b0000);
    std::vector<Vertex> nT;
    std::vector<Vertex> T;

    //Creation de non(nT)
    typedef property_map<Graph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);

    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
        Vertex v = *vp.first;
        if(index[v] >= 5)
        {
            nT.push_back(v);
        }else{
            T.push_back(v);
        }
    }

    //Calcule du cout de l'individu premier
    int val = f->calculeCout(p, g, nT);
    p.setCout(val);
    cout << "fitness = " << val << endl;

    //Test voisin
    Voisin * v = new SimpleVoisin(f);
    std::vector<Individu> voisins = v->getVoisin(p, g, nT);
    for(Individu i : voisins){
        cout << "id = " << i.getId() << " cout = " << i.getCout() << endl;
    }

    //Test recherche local
    RechercheLocal l(v);
    Individu best = l.recherche(p, g, nT);
    cout << "best : id = " << best.getId() << " cout = " << best.getCout() << endl;

    //Steiner
    Steiner s;
    s.generate(g, T, nT);
    return 0;
}