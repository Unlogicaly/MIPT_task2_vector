//
// Created by tarog on 05.12.2019.
//

#ifndef VECTOR_VERSION_19_VECTOR_H
#define VECTOR_VERSION_19_VECTOR_H

#include <iostream>
#include "tracer.h"


template <typename T, typename A>
struct vector_base {

    A alloc;

    T *elem;

    size_t sz;

    size_t space;

    vector_base(const A &a, size_t n) :
            alloc{a}, elem{a.allocate(n)}, sz{n}, space{n} {}

    ~vector_base() { alloc.deallocate(elem, space); }
};


template <typename T, typename A = std::allocator<T>>
class vector : private vector_base<T, A> {
  private:
    A alloc;

    size_t sz;

    T *elem;

    size_t space;

  public:
    explicit vector(size_t s);

    void reserve(size_t newalloc);

    size_t capacity() const { return space; }

    void resize(size_t newsize);

    void push_back(const T &d);

    vector(std::initializer_list<T> lst);

    vector(const vector<T, A> &other);

    vector(vector &&a);

    vector<T, A> &operator=(const vector<T, A> &a);

    vector<T, A> &operator=(vector &&a);

//    ~vector() {
//
//        for (size_t i = 0; i < sz; ++i)
//            alloc.destroy(&elem[i]);
//
//        alloc.deallocate(elem, sz);
//    }

    size_t size() const { return sz; }

    T operator[](size_t n) const { return elem[n]; }

    T &operator[](size_t n) { return elem[n]; }
};

template <typename T, typename A>
vector<T, A> &vector<T, A>::operator=(const vector<T, A> &a) {

    TRACE_FUNC;
    if (this == &a)
        return *this;

    if (a.sz < space) {

        for (size_t i = 0; i < a.sz; ++i)
            alloc.construct(&elem[i], a.elem[i]);

        sz = a.sz;
        return *this;
    }

    auto *p = alloc.allocate(a.sz);

    for (size_t i = 0; i < a.sz; ++i)
        alloc.construct(&p[i], a.elem[i]);

    for (size_t i = 0; i < sz; ++i)
        alloc.destroy(&elem[i]);

    alloc.deallocate(elem, sz);

    space = sz = a.sz;

    elem = p;

    return *this;
}

template <typename T, typename A>
vector<T, A>::vector(const vector<T, A> &other) :
        sz{other.sz},
        elem{alloc.allocate(other.sz)},
        space{other.space} {

    TRACE_FUNC;

    for (size_t i = 0; i < sz; ++i)
        alloc.construct(elem + i, *(other.elem + i));
}

template <typename T, typename A>
vector<T, A>::vector(std::initializer_list<T> lst) :
        sz{lst.size()},
        elem{alloc.allocate(lst.size())},
        space{lst.size()} {

    TRACE_FUNC;

    for (size_t i = 0; i < sz; ++i)
        alloc.construct(elem + i, *(lst.begin() + i));
}

template <typename T, typename A>
vector<T, A>::vector(size_t s) :
        sz{s},
        elem{alloc.allocate(sz)},
        space{sz} {

    TRACE_FUNC;

    for (int i = 0; i < sz; ++i)
        alloc.construct(&elem[i], T{});
}

template <typename T, typename A>
vector<T, A>::vector(vector<T, A> &&a) :
        sz{a.sz}, elem{a.elem}, space{sz} {

    TRACE_FUNC;

    a.sz = 0;
    a.elem = nullptr;
}

template <typename T, typename A>
vector<T, A> &vector<T, A>::operator=(vector<T, A> &&a) {

    TRACE_FUNC;

    for (size_t i = 0; i < sz; ++i)
        alloc.destroy(&elem[i]);

    alloc.deallocate(elem, sz);

    elem = a.elem;

    sz = a.sz;
    space = a.space;

    a.elem = nullptr;
    a.sz = 0;
    a.space = 0;

    return *this;
}

template <typename T, typename A>
void vector<T, A>::reserve(size_t newalloc) {

    TRACE_FUNC;

    if (newalloc <= space)
        return;
    T *p = alloc.allocate(newalloc);

    for (size_t i{0}; i < sz; ++i)
        alloc.construct(&p[i], elem[i]);

    for (size_t i = 0; i < sz; ++i)
        alloc.destroy(&elem[i]);

    alloc.deallocate(elem, sz);

    elem = p;

    space = newalloc;
}

template <typename T, typename A>
void vector<T, A>::resize(size_t newsize) {

    TRACE_FUNC;

    reserve(newsize);

    for (auto i = sz; i < newsize; ++i)
        alloc.construct(&elem[i], T{});

    sz = newsize;
}

template <typename T, typename A>
void vector<T, A>::push_back(const T &d) {

    TRACE_FUNC;

    if (space == 0)
        reserve(8);

    else if (sz == space)
        reserve(space * 2);

    alloc.construct(&elem[sz], d);

    ++sz;
}

#endif //VECTOR_VERSION_19_VECTOR_H
