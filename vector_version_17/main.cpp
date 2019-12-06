#include <iostream>
#include "vector.h"

int main() {

    vector a(10);  // �������� ������� ������ 10

    for (auto i = 0; i < a.size(); ++i)  // ����� size() ��������� ������ ������ �������
        a.set(i, i);  // ����� set() ��������� ���������� �������� ��������

    for (auto i = 0; i < a.size(); ++i)
        std::cout << a.get(i) << " ";  // ����� get() ��������� �������� �������� ��������

    std::cout << std::endl << a.get(-1) << std::endl;  // get �� ����������� ������������ ��������

    // a.set(11, 0);  // set ��� �� �� ����������� ������ �� �������, ������� ��� ������� ��������� ��������
    // ������������� �������� ��������� segmentation fault

    std::cout << typeid(a.get(0)).name();  // ��� ��������� �� ��������� double, ������� ��� ������

    //std::cout << a[0] // ������ �� ������������ �������� []

    return 0;
}