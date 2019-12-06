#include <iostream>
#include "vector.h"

int main() {

    vector a(10);  // —оздание вектора длиной 10
    std::cout << "First element: " << a.get(0) << "\nType: " << typeid(a.get(0)).name() << std::endl; // ¬се элементы
    // по-прежнему имеют неизмен€емый тип double, по умолчанию инициализируютс€ нул€ми

    vector b{0, 1, 2, 3, 4};  // —оздание вектора длиной п€ть при помощи списка инициализации

    vector c{b}; // —озздание вектора, использую конструктор копировани€

    std::cout << "vector 'c' values: \n";
    for (auto i = 0; i < c.size(); ++i) {  // размер также узнаЄтс€ методом size()
        std::cout << c[i] << " ";  // добавлен оператор []
    }

    std::cout << "\n";

    const vector d{std::move(c)};  // добавлен конструктор перемещени€

    std::cout << "vector 'd' values:\n";
    for (auto i = 0; i < d.size(); ++i) {
        std::cout << d[i] << " ";  // оператор [] также перегружен дл€ константных векторов
    }
    std::cout << "\n";

    a = b;  // добавлен оператор копирующего присваивани€

    b = std::move(vector{0, 1, 2, 3, 4});  // и перемещающего присваивани€

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