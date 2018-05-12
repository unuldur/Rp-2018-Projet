//
// Created by Unuldur on 21/03/2018.
//

#include <utility> #include <vector>
#include "Individu.h"
#include <limits.h>
Individu::Individu(std::vector<bool> id) : id(std::move(id)) {
}

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

void Individu::setId(std::vector<bool> id){
    Individu::id = id;
}

Individu::Individu(const Individu &id) : id(id.getId()), cout(id.getCout()) {

}

Individu::Individu(int cout, std::vector<bool> id) : cout(cout), id(std::move(id)) {}
