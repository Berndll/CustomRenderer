#include "../include/Matrix.hpp"

template <typename T> 
Matrix<T>::Matrix(int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        data.push_back(std::vector<T>());
        for (int j = 0; j < cols; ++j)
            data.back().push_back(T());
    }
}
