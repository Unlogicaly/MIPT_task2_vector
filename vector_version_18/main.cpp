#include <iostream>
#include "vector.h"

int main() {

    vector a(10);  // Создание вектора длиной 10
    std::cout << "First element: " << a.get(0) << "\nType: " << typeid(a.get(0)).name() << std::endl; // Все элементы
    // по-прежнему имеют неизменяемый тип double, по умолчанию инициализируются нулями

    vector b{0, 1, 2, 3, 4};  // Создание вектора длиной пять при помощи списка инициализации

    vector c{b}; // Созздание вектора, использую конструктор копирования

    std::cout << "vector 'c' values: \n";
    for (auto i = 0; i < c.size(); ++i) {  // размер также узнаётся методом size()
        std::cout << c[i] << " ";  // добавлен оператор []
    }

    std::cout << "\n";

    const vector d{std::move(c)};  // добавлен конструктор перемещения

    std::cout << "vector 'd' values:\n";
    for (auto i = 0; i < d.size(); ++i) {
        std::cout << d[i] << " ";  // оператор [] также перегружен для константных векторов
    }
    std::cout << "\n";

    a = b;  // добавлен оператор копирующего присваивания

    b = std::move(vector{0, 1, 2, 3, 4});  // и перемещающего присваивания

    std::cout << "vector 'a' values:\n";
    for (auto i = 0; i < a.size(); ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    std::cout << "vector 'b' values:\n";
    for (auto i = 0; i < b.size(); ++i) {
        std::cout << b[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
