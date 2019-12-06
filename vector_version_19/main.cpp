#include <iostream>
#include "vector.h"
//#include <vector>

using namespace std;

template <class T>
void print(const vector<T> &src,
           const std::string &sep = " ",
           const std::string &end = "\n",
           std::ostream &os = std::cout) {

    for (auto i = 0; i < src.size(); ++i) {
        os << src[i] << sep;
    }
    os << end;
}

struct Test_class {
    string a;

    Test_class(int i = 0) : a{"Hello"} {

        if (i > 990)
            throw runtime_error("");
    }
};

int main() {

    vector<int> o(10);
    cout << "vector 'o' values after default initializing:\n";
    print(o, " ", "\n\n");

    vector<int> a{0, 1, 2, 3};
    a.push_back(0);

    cout << "vector 'a' values after initializing with initializer_list and push_back 0:\n";
    print(a, " ", "\n\n");

    vector<int> b{a};

    vector<int> c{std::move(a)};

    cout << "vector 'b' values after initializing with copy constructor:\n";
    print(b, " ", "\n\n");

    cout << "vector 'c' values after initializing with move constructor:\n";
    print(c, " ", "\n\n");

    b = c;

    cout << "vector 'b' values after copy assignment:\n";
    print(b, " ", "\n\n");

    c = std::move(b);

    cout << "vector 'c' values after move assignment:\n";
    print(c, " ", "\n\n");

    c.resize(3);

    cout << "vector 'c' values after resizing to 3:\n";
    print(c, " ", "\n\n");

    c.reserve(10);

    cout << "vector 'c' values after reserving space 10:\n";
    print(c, " ", "\n\n");

    vector<vector<int>> d{{0, 1, 2, 3}};

    d.push_back({4, 5, 6, 7});

    cout << "2D vector 'd' values:\n";
    for (auto i = 0; i < d.size(); ++i)
        print(d[i]);

    for (auto i = 0; i < 1000; ++i) {
        vector<string> t{};
        for (auto j = 0; j < 1000; ++j)
            t.push_back("Hello");
    }

    for (auto i = 0; i < 10000; ++i) {
        vector<Test_class> t{};
        try {
            for (auto j = 0; j < 1000; ++j)
                t.push_back({j});
        }
        catch (...) {
        }
    }

    for (auto i = 0; i < 1000; ++i) {
        vector<vector<string>> t{};
        for (auto j = 0; j < 100; ++j) {
            t.push_back({});
            for (auto k = 0; k < 100; ++k)
                t[j].push_back("hello");
        }
    }

    return 0;
}