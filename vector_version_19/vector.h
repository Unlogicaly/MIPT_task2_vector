//
// Created by tarog on 05.12.2019.
//

#ifndef VECTOR_VERSION_19_VECTOR_H
#define VECTOR_VERSION_19_VECTOR_H

#include <iostream>
#include "tracer.h"


template <typename T, typename A>
struct vector_base {

    A *alloc;

    T *elem;

    size_t sz;

    size_t space;

    vector_base(A *a, size_t n) :
            alloc{a}, elem{a->allocate(n)}, sz{n}, space{n} {}
//
//    vector_base(const A &a, size_t n) :
//            alloc{a}, elem{a.allocate(n)}, sz{n}, space{n} {}

    ~vector_base() { alloc->deallocate(elem, space); }
};


template <typename T, typename A = std::allocator<T>>
class vector : private vector_base<T, A> {

  public:
    explicit vector(size_t s);

    void reserve(size_t newalloc);

    size_t capacity() const { return this->space; }

    void resize(size_t newsize);

    void push_back(const T &d);

    vector(std::initializer_list<T> lst);

    vector(const vector<T, A> &other);

    vector(vector &&a);

    vector<T, A> &operator=(const vector<T, A> &a);

    vector<T, A> &operator=(vector &&a);

    size_t size() const { return this->sz; }

    T operator[](size_t n) const { return this->elem[n]; }

    T &operator[](size_t n) { return this->elem[n]; }
};

template <typename T, typename A>
vector<T, A> &vector<T, A>::operator=(const vector<T, A> &a) {

    TRACE_FUNC;
    if (this == &a)
        return *this;

    if (a.sz < this->space) {

        for (size_t i = 0; i < a.sz; ++i)
            this->alloc->construct(&this->elem[i], a.elem[i]);

        this->sz = a.sz;
        return *this;
    }

    auto *p = this->alloc->allocate(a.sz);

    for (size_t i = 0; i < a.sz; ++i)
        this->alloc->construct(&p[i], a.elem[i]);

    for (size_t i = 0; i < this->sz; ++i)
        this->alloc->destroy(&this->elem[i]);

    this->alloc->deallocate(this->elem, this->sz);

    this->space = this->sz = a.sz;

    this->elem = p;

    return *this;
}

template <typename T, typename A>
vector<T, A>::vector(const vector<T, A> &other) :
        vector_base<T, A>(other.alloc, other.sz) {

    TRACE_FUNC;

    for (size_t i = 0; i < this->sz; ++i)
        this->alloc->construct(this->elem + i, *(other.elem + i));
}

template <typename T, typename A>
vector<T, A>::vector(std::initializer_list<T> lst) :
        vector_base<T, A>(new A, lst.size()) {

    TRACE_FUNC;

    for (size_t i = 0; i < this->sz; ++i)
        this->alloc->construct(this->elem + i, *(lst.begin() + i));
}

template <typename T, typename A>
vector<T, A>::vector(size_t s) :
        vector_base<T, A>(new A, s) {

    TRACE_FUNC;

    for (int i = 0; i < this->sz; ++i)
        this->alloc->construct(&this->elem[i], T{});
}

template <typename T, typename A>
vector<T, A>::vector(vector<T, A> &&a) :
        vector_base<T, A>(a.alloc, a.sz) {

    TRACE_FUNC;

    std::swap(this->elem, a.elem);
}

template <typename T, typename A>
vector<T, A> &vector<T, A>::operator=(vector<T, A> &&a) {

    TRACE_FUNC;

    for (size_t i = 0; i < this->sz; ++i)
        this->alloc->destroy(&this->elem[i]);

    this->alloc->deallocate(this->elem, this->sz);

    std::swap(this->sz, a.sz);
    std::swap(this->elem, a.elem);
    std::swap(this->space, a.space);

    return *this;
}

template <typename T, typename A>
void vector<T, A>::reserve(size_t newalloc) {

    TRACE_FUNC;

    if (newalloc <= this->space)
        return;
    T *p = this->alloc->allocate(newalloc);

    for (size_t i{0}; i < this->sz; ++i)
        this->alloc->construct(&p[i], this->elem[i]);

    for (size_t i = 0; i < this->sz; ++i)
        this->alloc->destroy(&this->elem[i]);

    this->alloc->deallocate(this->elem, this->sz);

    this->elem = p;

    this->space = newalloc;
}

template <typename T, typename A>
void vector<T, A>::resize(size_t newsize) {

    TRACE_FUNC;

    reserve(newsize);

    for (auto i = this->sz; i < newsize; ++i)
        this->alloc->construct(&this->elem[i], T{});

    this->sz = newsize;
}

template <typename T, typename A>
void vector<T, A>::push_back(const T &d) {

    TRACE_FUNC;

    if (this->space == 0)
        reserve(8);

    else if (this->sz == this->space)
        reserve(this->space * 2);

    this->alloc->construct(&this->elem[this->sz], d);

    ++this->sz;
}

#endif //VECTOR_VERSION_19_VECTOR_H
