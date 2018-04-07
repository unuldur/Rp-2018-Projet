//
// Created by Unuldur on 21/03/2018.
//

#ifndef PROJET_INDIVIDU_H
#define PROJET_INDIVIDU_H


class Individu {
    private:
        int cout;
        unsigned long id;
public:
    explicit Individu(unsigned long id);

    int getCout() const;

    void setCout(int cout);

    unsigned long getId() const;

    bool operator==(const Individu &rhs) const;

    bool operator!=(const Individu &rhs) const;
};


#endif //PROJET_INDIVIDU_H
