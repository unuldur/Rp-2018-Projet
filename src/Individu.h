//
// Created by Unuldur on 21/03/2018.
//

#ifndef PROJET_INDIVIDU_H
#define PROJET_INDIVIDU_H


#include "Graph.h"

class Individu {
    private:
        int cout;
        std::vector<bool> id;
    public:
        Individu(std::vector<bool> id);
        Individu(const Individu& i);
        Individu();

        int getCout() const;

        void setCout(int cout);

        std::vector<bool> getId() const;

        bool operator==(const Individu &rhs) const;

        bool operator!=(const Individu &rhs) const;

        void setId(std::vector<bool> id);
};


#endif //PROJET_INDIVIDU_H
