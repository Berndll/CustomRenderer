#pragma once

#include <iostream>
#include <initializer_list>
#include <vector>

template<typename T>
class Matrix {
    using vec2 = std::vector<std::vector<T>>;

    struct Size {
        int rows;
        int cols;
    };

public:
    Matrix(int rows, int cols);
    Matrix(std::initializer_list<T> list);

    T& at(int row, int col) { return _data.at(row).at(col); }

    bool setSize(int rows, int cols);
    typename Matrix<T>::Size getSize();
    void print();

    Matrix<T> operator+(const Matrix<T>& other) const;
    Matrix<T> operator-(const Matrix<T>& other) const;
    Matrix<T>& operator=(std::initializer_list<std::initializer_list<T>> list);
    Matrix<T>& operator=(const Matrix<T> other);
    Matrix<T>& operator+=(const Matrix<T> other);
    Matrix<T>& operator-=(const Matrix<T> other);    

private:
    int _rows, _cols;
    vec2 _data;

    template<typename Func>
    Matrix<T>& assignmentOperation(const Matrix<T>& other, Func op);
    template<typename Func>
    Matrix<T> binaryOperation(const Matrix<T>& other, Func op) const;
};

template<typename T>
Matrix<T>::Matrix(int rows, int cols) : _rows(rows), _cols(cols), _data(rows, std::vector<T>(cols)) {
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<T> list) {

}

template<typename T>
bool Matrix<T>::setSize(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Invalid matrix size!");
        exit(0);
    }

    _rows = rows;
    _cols = cols;

    _data.resize(_rows);
    for (auto& vec : _data) {  
        vec.resize(_cols);
    }
    
    return true;
}

template<typename T>
typename Matrix<T>::Size Matrix<T>::getSize() {
    return { _rows, _cols };
}

template<typename T>
void Matrix<T>::print() {
    std::cout
        << "- Size: {"
        << getSize().rows
        << ", "
        << getSize().cols
        << "}"
        << std::endl;

    std::cout << "- Values: {\n";
    for (auto& vec : _data) {
        std::cout << "   { ";
        for (auto val : vec) {
            std::cout << val << ", ";
        }
        std::cout << "}\n";
    }
    std::cout << "}" << std::endl;
}

template<typename T>
template<typename Func>
Matrix<T>& Matrix<T>::assignmentOperation(const Matrix<T>& other, Func op) {
    if (_rows != other._rows || _cols != other._cols)
        throw std::invalid_argument("Matrix dimensions must match for operation.");
    
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _cols; ++j)
            op(_data[i][j], other._data[i][j]);
}

template<typename T>
template<typename Func>
Matrix<T> Matrix<T>::binaryOperation(const Matrix<T>& other, Func op) const {
    if (_rows != other._rows || _cols != other._cols)
        throw std::invalid_argument("Matrix dimensions must match for operation.");

    Matrix<T> result(_rows, _cols);
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            result._data[i][j] = op(_data[i][j], other._data[i][j]);
        }
    }
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> list) {
    if (_rows != list.size() || _cols != list.begin()->size())
        throw std::invalid_argument("Matrix dimensions must match for operation.");
    _data = vec2(list.begin(), list.end());
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> other) {
    return assignmentOperation(other, [](T& a, T b) { return a = b; });
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    return binaryOperation(other, [](T a, T b) { return a + b; });
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    return binaryOperation(other, [](T a, T b) { return a - b; });
}


template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T> other) {
    return assignmentOperation(other, [](T& a, T b) { return a += b; });
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T> other) {
    return assignmentOperation(other, [](T& a, T b) { return a += b; });
}