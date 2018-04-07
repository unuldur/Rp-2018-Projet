//
// Created by Unuldur on 21/03/2018.
//

#include "Individu.h"

Individu::Individu(unsigned long id) : id(id) {}

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

unsigned long Individu::getId() const {
    return id;
}
