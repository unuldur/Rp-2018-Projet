//
// Created by Unuldur on 21/03/2018.
//

#include "Individu.h"
#include <limits.h>
Individu::Individu(std::vector<bool> id) : id(id) {}

int Individu::getCout() const {
    return cout;
}

void Individu::setCout(int cout) {
    Individu::cout = cout;
}

bool Individu::operator==(const Individu &rhs) const {
    return id == rhs.id;
}

bool Individu::operator!=(const Individu &rhs) const {
    return !(rhs == *this);
}

std::vector<bool> Individu::getId() const {
    return id;
}

Individu::Individu() {
    cout = INT_MAX;
}
