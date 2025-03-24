#pragma once

#include "Matrix.hpp"

template<typename T>
class Vector : public Matrix<T> {
public:
    Vector(int rows);

private:
};

template<typename T>
Vector<T>::Vector(int rows) : Matrix<T>::Matrix(rows, 1) {
}