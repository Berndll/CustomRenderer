#pragma once

#include "Vector.hpp"

template <typename T>
class Matrix {
public:
    Matrix(int rows, int cols);  
    Matrix(std::initializer_list<std::initializer_list<T>> il);
    Matrix(std::string path);

    const int getRows() { return _rows; }
    const int getCols() { return _cols; }

    T& at(int row, int col) { return _mat.at(row).at(col); }
    Vector<T>& at(int row) { return _mat.at(row); }

    void print();
    static Vector<T> project(Vector<T> v, T near_clip, T far_clip, T fov);
    void resize() { this->resize(_rows, _cols); }
    void resize(int rows, int cols);

    static void setProjectionMatrix(const double fov, const double near_clip, const double far_clip, Matrix<T>& m);
    static void multPointMatrix(Vector<T> in, Vector<T>& out, const Matrix<T> m);

private:
    Vector<Vector<T>> _mat;
    int _rows, _cols;
    T _fov, _near, _far;
};

template <typename T>
Matrix<T>::Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
    this->resize(_rows, _cols);
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> il) :
    Matrix<T>::Matrix(il.size(), il.size() ? il.begin()->size() : 0) {
    int r = 0, c = 0;

    for (auto& row : il) {
        for (auto& item : row)
            this->at(r, c++) = item;
        c = 0;
        ++r;
    }
}

template<typename T>
Matrix<T>::Matrix(std::string path) {
    std::string str;
    std::ifstream input;
    input.open(path, std::ios::in);

    if (!input.is_open())
        throw std::runtime_error("File is not open: " + path);

    int row = 0, col = 0;

    while (std::getline(input, str)) {
        size_t splitPos;
        _mat.emplace_back();

        do {
            splitPos = str.find(',');
            if (splitPos == std::string::npos)
                splitPos = str.find("\n");

            std::stringstream ss(str.substr(0, splitPos));
            T value;
            ss >> value;

            _mat.at(row).push_back(value);
            str = str.substr(splitPos + 1);
            col++;
        } while (splitPos != std::string::npos);
        col = 0;
        row++;
    }

    _rows = row;
    _cols = _mat.at(0).size();

    input.close();
}

template<typename T> 
void Matrix<T>::print() {
    for (int r = 0; r < _rows; ++r) {    
        for (int c = 0; c < _cols; ++c)
            std::cout << this->at(r, c) << "\t";
        std::cout << "\n";
    }
    std::cout << std::endl;    
}

template<typename T>
void Matrix<T>::resize(int rows, int cols) {
    _rows = rows;
    _cols = cols;
    _mat.resize(rows);

    for (int i = 0; i < rows; ++i)
        _mat.at(i).resize(cols);
}

template<typename T>
Vector<T> operator*=(Vector<T>& v, Matrix<T> m) {
    Vector<T> result(m.getCols(), 0);

    std::cout << "Vector: " << '\n';
    v.print();

    std::cout << "Matrix: " << '\n';
    m.print();

    std::cout << "\n\n";

    for (int c = 0; c < m.getCols(); ++c) {
        for (int r = 0; r < m.getRows(); ++r) {
            std::cout << "(" << r << "," << c << ") ";
            result.at(c) += v.at(r) * m.at(r, c);
        }
        std::cout << std::endl;
    }
    
    v = result;
}

template<typename T>
void Matrix<T>::setProjectionMatrix(const double fov, const double near_clip, const double far_clip, Matrix<T>& m) {
    double clip = -far_clip / (far_clip - near_clip);
    double scale = 1 / tan(fov * M_PI_2 / 180);

    m = {
        { scale,      0,                0,  0}, 
        {     0,  scale,                0,  0}, 
        {     0,      0,             clip, -1}, 
        {     0,      0, clip * near_clip,  0}
    };
}