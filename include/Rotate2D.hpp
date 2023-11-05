// #pragma once

// #include <math.h>

// #include "Matrix2D.hpp"

// class Rotate2D {
// public:
//     static void rotate(std::vector<Matrix2D<double>> points, Matrix2D<double> rotPoint, double deg);
// };

// void Rotate2D::rotate(std::vector<Matrix2D<double>> points, Matrix2D<double> rotPoint, double deg) {
//     Matrix2D<double> rotMat(2,2);
//     rotMat.at(0,0) =  cos(deg);
//     rotMat.at(1,0) =  sin(deg);
//     rotMat.at(0,1) = -sin(deg);
//     rotMat.at(1,1) =  cos(deg);

//     for (int i = 0; i < points.size(); ++i) {
//         points.at(i) -= rotPoint;
//         points.at(i) = Matrix2D<double>::dotProduct(rotMat, points.at(i));
//         points.at(i) += rotPoint;
//     }
// }