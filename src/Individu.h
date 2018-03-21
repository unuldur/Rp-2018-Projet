//
// Created by Unuldur on 21/03/2018.
//

#ifndef PROJET_INDIVIDU_H
#define PROJET_INDIVIDU_H


class Individu {
    private:
        int cout;
        int id;
public:
    explicit Individu(int id);

    int getCout() const;

    void setCout(int cout);

    int getId() const;

    bool operator==(const Individu &rhs) const;

    bool operator!=(const Individu &rhs) const;
};


#endif //PROJET_INDIVIDU_H
