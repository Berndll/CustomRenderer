#pragma once

#include <iostream>
#include <vector>

template<typename T>
class Matrix2D {
public:
    Matrix2D(int rows, int cols);
    Matrix2D(std::vector<std::vector<T>> m);

    const int getRows() { return _rows; }
    const int getCols() { return _cols; }

    void setData(Matrix2D<T> m) { *this = m; }
    void setData(std::vector<std::vector<T>> v) { *this = v; }

    T& at(int row, int col) { return _data.at(row).at(col); }

    void print();
    void resize(int rows, int cols) { _data.resize(rows, std::vector<T>(cols, T())); }
    void rotate(Matrix2D<double> rotPoint, double deg);

    Matrix2D<T> transform(Matrix2D<T> camera, Matrix2D<T> theta);
    Matrix2D<T> project(Matrix2D<T> point, Matrix2D<T> plane);

    static void rotate(std::vector<Matrix2D<double>>& points, Matrix2D<double> rotPoint, double deg);
    static Matrix2D<T> dotProduct(Matrix2D<T> Matrix2D0, Matrix2D<T> Matrix2D1);

    Matrix2D<T>& operator=  (Matrix2D<T> m) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) = m.at(r, c);
    }
    Matrix2D<T>& operator=  (std::vector<std::vector<T>> v) {
        for (int r = 0; r < _rows; ++r)
            for (int c = 0; c < _cols; ++c)
                at(r, c) = v.at(r).at(c);
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
    resize(rows, cols);
}

template <typename T>
Matrix2D<T>::Matrix2D(std::vector<std::vector<T>> m) {
    _rows = m.size();
    _cols = m.at(0).size();

    resize(_rows, _cols);

    for (int r = 0; r < _rows; ++r)
        for (int c = 0; c < _cols; ++c)
            at(r, c) = m.at(r).at(c);
}

template <typename T> 
Matrix2D<T> Matrix2D<T>::dotProduct(Matrix2D<T> Matrix0, Matrix2D<T> Matrix1) {
    if (Matrix0.getCols() != Matrix1.getRows())
        throw std::invalid_argument("Unmatching Matrix2D sizes\n");

    Matrix2D<T> result(Matrix0.getRows(), Matrix1.getCols());
    result = 0;

    for (int r = 0; r < result.getRows(); ++r)
        for (int c = 0; c < result.getCols(); ++c)
            for (int i = 0; i < Matrix0.getCols(); ++i)
                result.at(r, c) += Matrix0.at(r, i) * Matrix1.at(i, c);

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
void Matrix2D<T>::rotate(Matrix2D<double> rotPoint, double deg) {
    if (_cols != 1 && _rows != 2)
        throw std::invalid_argument("Wrong matrix size (2x1 needed)");

    Matrix2D<double> rotMat(2,2);
    rotMat.at(0,0) =  cos(deg);
    rotMat.at(1,0) =  sin(deg);
    rotMat.at(0,1) = -sin(deg);
    rotMat.at(1,1) =  cos(deg);

    *this -= rotPoint;
    *this = Matrix2D<double>::dotProduct(rotMat, *this);
    *this += rotPoint;
}

template <typename T> 
void Matrix2D<T>::rotate(std::vector<Matrix2D<double>>& points, Matrix2D<double> rotPoint, double deg) {
    for (auto p : points)
        if (p.getCols() != 1 && p.getRows() != 2)
            throw std::invalid_argument("Wrong matrix size (2x1 needed)");

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

template <typename T>
Matrix2D<T> Matrix2D<T>::transform(Matrix2D<T> camera, Matrix2D<T> theta) {
    Matrix2D<T> tempDiff(3,1);
    tempDiff = *this;
    tempDiff -= camera;
    
    Matrix2D<T> result(3,3);

    static Matrix2D<T> multiMatrix0(3,3);
    multiMatrix0 = 0;
    multiMatrix0.at(0,0) =  1;
    multiMatrix0.at(1,1) =  cos(theta.at(0,0));
    multiMatrix0.at(2,1) = -sin(theta.at(0,0));
    multiMatrix0.at(1,2) =  sin(theta.at(0,0));
    multiMatrix0.at(2,2) =  cos(theta.at(0,0));
    
    static Matrix2D<T> multiMatrix1(3,3);
    multiMatrix1 = 0;
    multiMatrix1.at(0,0) =  cos(theta.at(1,0));
    multiMatrix1.at(2,0) =  sin(theta.at(1,0));
    multiMatrix1.at(1,1) =  1;
    multiMatrix1.at(0,2) = -sin(theta.at(1,0));
    multiMatrix1.at(2,2) =  cos(theta.at(1,0));

    static Matrix2D<T> multiMatrix2(3,3);
    multiMatrix2 = 0;
    multiMatrix2.at(0,0) =  cos(theta.at(2,0));
    multiMatrix2.at(1,0) = -sin(theta.at(2,0));
    multiMatrix2.at(0,1) =  sin(theta.at(2,0));
    multiMatrix2.at(1,1) =  cos(theta.at(2,0));
    multiMatrix2.at(2,2) =  1;

    // result = multiMatrix0;
    result = dotProduct(multiMatrix0, multiMatrix1);
    result = dotProduct(result, multiMatrix2);

    // result.print();

    Matrix2D<double> realResult(3,1);

    realResult = dotProduct(result, tempDiff);

    // result = dotProduct(result, tempDiff);
    
    // for (auto t : tempDiff)
        // std::cout << t < " ";
    // tempDiff.print();
    // realResult.print();

    return realResult;
}

template <typename T>
Matrix2D<T> Matrix2D<T>::project(Matrix2D<T> point, Matrix2D<T> plane) {
    Matrix2D<T> result(2,1);

    result.at(0,0) = 
        (plane.at(2,0) * point.at(0,0) / point.at(2,0)) + plane.at(0,0); 
    result.at(1,0) = 
        (plane.at(2,0) * point.at(1,0) / point.at(2,0)) + plane.at(1,0); 

    return result;
}

template <typename T>
std::vector<T>& operator* (const Matrix2D<T> m, const std::vector<T> v) {
    std::vector<T> result(m.getRows(), 0);

    for (int r = 0; r < m.getRows(); ++r)
        for (int c = 0; c < m.getCols(); ++c)
            result.at(r) += m.at(r, c) * v.at(r);

    return result;
}