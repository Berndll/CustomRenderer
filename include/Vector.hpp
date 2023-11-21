#pragma once

#include <fstream>
#include <iostream>
#include <vector>

template<typename T>
class Vector {
public:
    Vector() {}
    Vector(std::initializer_list<T> v) { _vec.assign(v.begin(), v.end()); }
    Vector(std::string path);

    T& at(int index) { return _vec.at(index); }
    void print() { for (T v : _vec) { std::cout << v << " "; } std::cout << std::endl; }
    void push_back(T n) { _vec.push_back(n); }
    void resize(int size) { _vec.resize(size); }
    const int size() { return _vec.size(); }

    Vector<T>& operator=(Vector<T> v);
    Vector<T>& operator=(std::initializer_list<T> v);
    Vector<T>& operator+=(Vector<T> v);
    Vector<T>& operator-=(Vector<T> v);

    bool operator==(Vector<T> v);

    Vector<T> strSplit(std::string str, const char splitChar = ',');
private:
    std::vector<T> _vec;

    void sizeCheck(Vector<T> a, Vector<T> b) { if (a.size() != b.size()) std::runtime_error("Unmatching vector sizes."); }
};

template<typename T>
Vector<T>::Vector(std::string path) {
    std::string str;
    std::fstream input;
    input.open(path.c_str(), std::ios::in);

    if (!input.is_open())
        throw std::runtime_error("File is not open: " + path);

    while (std::getline(input, str))
        *this = strSplit(str);

    input.close();
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> v) {
    if (this != &v) {
        _vec.resize(v.size());
        for (int i = 0; i < size(); ++i)
            _vec.at(i) = v.at(i);
    }
    return *this;
}
template<typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> v) {
    _vec.assign(v.begin(), v.end());
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator+=(Vector<T> v) {
    sizeCheck(*this, v);
    for (int i = 0; i < size(); ++i)
        _vec.at(i) += v.at(i);
    return *this;
}
template<typename T>
Vector<T>& Vector<T>::operator-=(Vector<T> v) {
    sizeCheck(*this, v);
    for (int i = 0; i < size(); ++i)
        _vec.at(i) -= v.at(i);
    return *this;
}

template<typename T>
bool Vector<T>::operator==(Vector<T> v) {
    sizeCheck(*this, v);
    for (int i = 0; i < _vec.size(); ++i)
        if (_vec.at(i) != v.at(i)) 
            return 0;
    return 1;
}

template<typename T>
Vector<T> Vector<T>::strSplit(std::string str, const char splitChar) {
    std::string tempStr;
    Vector<T> vecResult = {};
    size_t splitPos;
    long double temp;

    do {
        splitPos = str.find(splitChar);
        if (splitPos == std::string::npos)
            splitPos = str.find("\n");

        temp = std::stod(str.substr(0, splitPos));

        vecResult.push_back(static_cast<T>(temp));

        str = str.substr(splitPos + 1);
    } while (splitPos != std::string::npos);

    // vecResult.print();

    return vecResult;
}