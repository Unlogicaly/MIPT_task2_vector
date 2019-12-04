//
// Created by tarog on 05.12.2019.
//

#ifndef VECTOR_VERSION_18_VECTOR_H
#define VECTOR_VERSION_18_VECTOR_H

class vector {
  private:
    size_t sz;

    double *elem;

  public:
    explicit vector(size_t s);

    vector(std::initializer_list<double> lst);

    vector(const vector &other);

    vector(vector &&a);

    vector &operator=(const vector &a);

    vector &operator=(vector &&a);

    ~vector() { delete[] elem; }

    int size() const { return sz; }

    double get(int n) const { return elem[n]; }

    void set(int n, double v) { elem[n] = v; }

    double operator[](size_t n) const { return elem[n]; }

    double &operator[](size_t n) { return elem[n]; }
};

#endif //VECTOR_VERSION_18_VECTOR_H
