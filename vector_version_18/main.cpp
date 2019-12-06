#include <iostream>
#include "vector.h"

int main() {

    vector a(10);  // �������� ������� ������ 10
    std::cout << "First element: " << a.get(0) << "\nType: " << typeid(a.get(0)).name() << std::endl; // ��� ��������
    // ��-�������� ����� ������������ ��� double, �� ��������� ���������������� ������

    vector b{0, 1, 2, 3, 4};  // �������� ������� ������ ���� ��� ������ ������ �������������

    vector c{b}; // ��������� �������, ��������� ����������� �����������

    std::cout << "vector 'c' values: \n";
    for (auto i = 0; i < c.size(); ++i) {  // ������ ����� ������� ������� size()
        std::cout << c[i] << " ";  // �������� �������� []
    }

    std::cout << "\n";

    const vector d{std::move(c)};  // �������� ����������� �����������

    std::cout << "vector 'd' values:\n";
    for (auto i = 0; i < d.size(); ++i) {
        std::cout << d[i] << " ";  // �������� [] ����� ���������� ��� ����������� ��������
    }
    std::cout << "\n";

    a = b;  // �������� �������� ����������� ������������

    b = std::move(vector{0, 1, 2, 3, 4});  // � ������������� ������������

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