#pragma once

#include <iostream>
#include <vector>

template<typename T>
class Vector {
public:
    Vector() {}

    T& at(int index) { return _vec.at(index); }
    void print() { for (T v : _vec) { std::cout << v << " "; } std::cout << std::endl; }
    void push_back(T n) { _vec.push_back(n); }
    void resize(int size) { _vec.resize(size); }
    const int size() { return _vec.size(); }

    Vector<T>& operator=(Vector<T> v);
    Vector<T>& operator=(std::initializer_list<T> v);

private:
    std::vector<T> _vec = {0};

    void sizeCheck(int a, int b) { if (a != b) std::runtime_error("Unmatching vector sizes."); }
};