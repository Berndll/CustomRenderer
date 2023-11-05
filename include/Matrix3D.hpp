#pragma once

#include "Matrix2D.hpp"

template<typename T>
class Matrix3D {
public:
    Matrix3D(int rows, int cols, int pages);

    void print();


private:
    int _rows, _cols, _pages;
    std::vector<Matrix2D<double>> _data;
};

template<typename T>
Matrix3D<T>::Matrix3D(int rows, int cols, int pages) : _rows(rows), _cols(cols), _pages(pages) {
    for (int i = 0; i < _pages; ++i) {
        _data.push_back(Matrix2D<double>(_rows, _cols));
    }
}

template<typename T>
void Matrix3D<T>::print() {
    for (int i = 0; i < _pages; ++i) {
        _data.at(i).print();
        std::cout << "\n\n";
    }
}