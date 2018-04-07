//
// Created by Unuldur on 07/04/2018.
//

#ifndef PROJET_PARSER_H
#define PROJET_PARSER_H


#include <vector>
#include "../Graph.h"

class Parser {
public:
    static Graph readGraph(const std::string & file, std::vector<int> * T);

private:
    Parser(){}
};


#endif //PROJET_PARSER_H
