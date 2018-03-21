#include <iostream>

#include <fstream>
#include "src/Graph.h"
#include "src/Fitness.h"
#include "src/SimpleFitness.h"

using namespace std;
int main() {
    const int num_nodes = 9;
    E edge_array[] = { E(0, 1), E(0, 2), E(0, 5), E(0, 7), E(1, 5),
                       E(1, 4), E(1, 8), E(2, 7), E(2, 6), E(2,3),
                       E(3, 6), E(4, 6), E(4, 8), E(5, 6)
    };
    int weights[] = { 8, 9, 2, 2, 2, 5, 8, 8, 4, 8, 3, 5, 8, 1};
    std::size_t num_edges = sizeof(edge_array) / sizeof(E);
    Graph g(edge_array, edge_array + num_edges, weights, num_nodes);

    SimpleFitness f;
    Individu p(0b11111);
    std::vector<Vertex> T;
    typedef property_map<Graph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);

    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
        Vertex v = *vp.first;
        if(index[v] >= 5 or index[v] == 0)
        {
            T.push_back(v);
        }
    }
    int val = f.calculeCout(&p, g, T);
    std::cout << "fitness = " << val << std::endl;
    return 0;
}