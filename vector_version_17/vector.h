//
// Created by tarog on 04.12.2019.
//

#ifndef VECTOR_VERSION_17_VECTOR_H
#define VECTOR_VERSION_17_VECTOR_H

class vector {
  private:
    int sz;

    double *elem;

  public:
    vector(int s) : sz{s}, elem{new double[s]} {

        for (int i = 0; i < s; ++i)
            elem[i] = 0;
    }

    ~vector() { delete[] elem; }

    int size() const { return sz; }

    double get(int n) const { return elem[n]; }

    void set(int n, double v) { elem[n] = v; }
};

#endif //VECTOR_VERSION_17_VECTOR_H
