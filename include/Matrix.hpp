#pragma once

#include <vector>

template<typename T>
class Matrix {
public:
    Matrix(int rows, int cols);

    std::vector<std::vector<T>> data;
    // T at(int row, int col) { return data.at(row).at(col); }
    

private:
};