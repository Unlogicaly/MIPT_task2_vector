//
// Created by tarog on 05.12.2019.
//

#include <iostream>
#include "vector.h"

vector &vector::operator=(const vector &a) {

    auto *p = new double[a.sz];
    std::copy(a.elem, a.elem + a.sz, p);
    delete[]elem;
    elem = p;
    sz = a.sz;
    return *this;
}

vector::vector(const vector &other) :
        sz{other.sz},
        elem{new double[other.sz]} {

    std::copy(other.elem, other.elem + sz, elem);
}

vector::vector(std::initializer_list<double> lst) :
        sz{lst.size()},
        elem{new double[lst.size()]} {

    std::copy(lst.begin(), lst.end(), elem);
}

vector::vector(size_t s) :
        sz{s},
        elem{new double[sz]} {

    for (int i = 0; i < sz; ++i)
        elem[i] = 0.0;
}

vector::vector(vector &&a) :
        sz{a.sz}, elem{a.elem} {

    a.sz = 0;
    a.elem = nullptr;
}

vector &vector::operator=(vector &&a) {

    delete[]elem;
    elem = a.elem;
    sz = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}