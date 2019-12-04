#include <iostream>
#include "vector.h"

int main() {

    vector a(10);

    for (auto i = 0; i < 10; ++i)
        a.set(i, i);

    for (auto i = 0; i < 10; ++i)
        std::cout << a.get(i);

    return 0;
}