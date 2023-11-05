#pragma once

#include <iostream>
#include <vector>

template<typename T>
class Matrix2D {
public:
    Matrix2D(int rows, int cols);

    const int getRows() { return _rows; }
    const int getCols() { return _cols; }

    // void setData() {}

    T& at(int row, int col) { return _data.at(row).at(col); }

    void print();
    void resize(int rows, int cols) { _data.resize(rows, std::vector<T>(cols, T())); }
    static void rotate(std::vector<Matrix2D<double>>& points, Matrix2D<double> rotPoint, double deg);

    static Matrix2D<T> dotProduct(Matrix2D<T> Matrix2D0, Matrix2D<T> Matrix2D1);

    Matrix2D<T>& operator=  (Matrix2D<T> m) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) = m.at(r, c);
    }
    Matrix2D<T>& operator=  (const double n) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) = n;
        return *this;
    }
    Matrix2D<T>& operator+= (Matrix2D<T> m) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) += m.at(r, c);
        return *this;
    }
    Matrix2D<T>& operator+= (const double n) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) += n;
        return *this;
    }
    Matrix2D<T>& operator-= (Matrix2D<T> m) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) -= m.at(r, c);
        return *this;
    }
    Matrix2D<T>& operator-= (const double n) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) -= n;
        return *this;
    }
    Matrix2D<T>& operator*= (const double n) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) *= n;
        return *this;
    }
    Matrix2D<T>& operator/= (const double n) {
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
Matrix2D<T>::Matrix2D(int rows, int cols) : _rows(rows), _cols(cols) {
    /*
    // for (int r = 0; r < rows; ++r) {
    //     _data.push_back(std::vector<T>());
    //     for (int c = 0; c < cols; ++c)
    //         _data.back().push_back(T());
    // }*/
    _data.resize(rows, std::vector<T>(cols, T()));
}

template <typename T> 
Matrix2D<T> Matrix2D<T>::dotProduct(Matrix2D<T> Matrix2D0, Matrix2D<T> Matrix2D1) {
    if (Matrix2D0.getCols() != Matrix2D1.getRows())
        throw std::invalid_argument("Unmatching Matrix2D sizes\n");

    Matrix2D<T> result(Matrix2D0.getRows(), Matrix2D1.getCols());
    result = 0;

    for (int r = 0; r < result.getRows(); ++r)
        for (int c = 0; c < result.getCols(); ++c)
            for (int i = 0; i < Matrix2D0.getCols(); ++i)
                result.at(r, c) += Matrix2D0.at(r, i) * Matrix2D1.at(i, c);

    return result;
}

template <typename T> 
void Matrix2D<T>::print() {
    for (int r = 0; r < _rows; ++r) {
        for (int c = 0; c < _cols; ++c) {
            std::cout << at(r, c) << "\t";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;    
}

template <typename T> 
void Matrix2D<T>::rotate(std::vector<Matrix2D<double>>& points, Matrix2D<double> rotPoint, double deg) {
    Matrix2D<double> rotMat(2,2);
    rotMat.at(0,0) =  cos(deg);
    rotMat.at(1,0) =  sin(deg);
    rotMat.at(0,1) = -sin(deg);
    rotMat.at(1,1) =  cos(deg);

    for (int i = 0; i < points.size(); ++i) {
        points.at(i) -= rotPoint;
        points.at(i) = Matrix2D<double>::dotProduct(rotMat, points.at(i));
        points.at(i) += rotPoint;
    }
}