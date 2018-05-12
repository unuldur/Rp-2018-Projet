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
#include "src/genetic/Generation.h"
#include "src/genetic/Selection.h"
#include "src/genetic/Croisement.h"
#include "src/genetic/Mutation.h"
#include "src/genetic/Remplacement.h"
#include "src/genetic/Genetic.h"

using namespace std;

void printIndividu(Individu i){
    for(bool b : i.getId()){
        cout << b;
    }
    cout << " " << i.getCout() << endl;
}

void test1(){
    std::vector<int> terminaux;
    //test parser
    Graph g = Parser::readGraph("../resources/C/c04.stp", &terminaux);

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
    RandomiseGeneration rg(&acm);
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
    Individu best = l.recherche(rg, g, T, nT, *f, 300);
    cout << "best :" << " cout = " << best.getCout() << endl;

    end = std::chrono::system_clock::now();

    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
            (end-start).count();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds << "s\n";
}

void test2(){
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
}

void test3(){
    std::vector<int> terminaux;
    //Graph g = Parser::readGraph("../resources/C/c04.stp", &terminaux);

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
    terminaux.push_back(1);
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


    Steiner s;
    RandomiseGeneration rg(&s);
    Generation generation(&rg);
    std::vector<Individu> individus = generation.genere(g, T, nT, 4);
    cout << "individus" << endl;
    for(Individu i : individus){
        i.setCout(f->calculeCout(i, g, nT));
        printIndividu(i);
        cout << endl;
    }
    Selection selection;
    std::vector<Individu> parents = selection.select(individus);
    cout << "parents" << endl;
    for(Individu i : parents){
        printIndividu(i);
        cout << endl;
    }
    Croisement croisement(nT.size()/2);
    std::vector<Individu> enfants = croisement.croise(parents);
    cout << "enfants" << endl;
    for(Individu i : enfants){
        printIndividu(i);
        cout << endl;
    }
    Mutation mutation(0.03);
    mutation.mutate(enfants);
    cout << "enfants mutes" << endl;
    for(Individu i : enfants){
        i.setCout(f->calculeCout(i, g, nT));
        printIndividu(i);
        cout << endl;
    }
    Remplacement remplacement;
    std::vector<Individu> individuNew  = remplacement.remplace(individus, enfants, *f, g, nT);
    cout << "new gen" << endl;
    for(Individu i : individuNew){
        printIndividu(i);
        cout << endl;
    }

    Genetic genetic(&generation, &selection, &croisement, &mutation, &remplacement);
    Individu best  = genetic.algoGenetic(g, T, nT, 200, 50, *f);
    cout << "best  = ";
    printIndividu(best);



}

int main() {
    test3();


    return 0;
}
