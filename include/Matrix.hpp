#pragma once

#include <iostream>
#include <vector>

template<typename T>
class Matrix {
public:
    Matrix(int rows, int cols);

    const int getRows() { return _rows; }
    const int getCols() { return _cols; }

    T& at(int row, int col) { return _data.at(row).at(col); }

    void print();

    static Matrix<T> dotProduct(Matrix<T> matrix0, Matrix<T> matrix1);

    Matrix<T>& operator=  (Matrix<T> m) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) = m.at(r, c);
    }
    Matrix<T>& operator=  (const double n) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) = n;
        return *this;
    }
    Matrix<T>& operator+= (const double n) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) += n;
        return *this;
    }
    Matrix<T>& operator-= (const double n) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) -= n;
        return *this;
    }
    Matrix<T>& operator*= (const Matrix<T> m) { 
        return dotProduct(this, m); 
    }
    Matrix<T>& operator*= (const double n) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) *= n;
        return *this;
    }
    Matrix<T>& operator/= (const double n) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) /= n;
        return *this;
    }

private:
    std::vector<std::vector<T>> _data;
    int _rows, _cols;
};

template <typename T>
Matrix<T>::Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
    for (int r = 0; r < rows; ++r) {
        _data.push_back(std::vector<T>());
        for (int c = 0; c < cols; ++c)
            _data.back().push_back(T());
    }
    // _data.resize(_rows);
    // for (int r = 0; r < _rows; ++r)
    //     _data.at(r).resize(_cols);
    // this = 0;
}

template <typename T> 
Matrix<T> Matrix<T>::dotProduct(Matrix<T> matrix0, Matrix<T> matrix1) {
    if (matrix0.getCols() != matrix1.getRows()) {
        throw std::invalid_argument("Unmatching matrix sizes\n");
    }

    Matrix<T> result(matrix0.getRows(), matrix1.getCols());
    result = 0;

    for (int r = 0; r < result.getRows(); ++r)
        for (int c = 0; c < result.getCols(); ++c)
            for (int i = 0; i < matrix0.getCols(); ++i)
                result.at(r, c) += matrix0.at(r, i) * matrix1.at(i, c);

    return result;
}

template <typename T> 
void Matrix<T>::print() {
    for (int r = 0; r < _rows; ++r) {
        for (int c = 0; c < _cols; ++c) {
            std::cout << at(r, c) << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n" << std::endl;    
}