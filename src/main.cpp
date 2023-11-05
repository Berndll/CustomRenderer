#include <iostream>
#include <math.h>
#include <vector>

#include "Window.hpp"

#define FPS 100 // default = 100

int main() {
    Window window;

    // Matrix3D<double> threeD (3,3,3);
    // threeD.print();

    // return 0;

    Matrix2D<double> rotPoint(2,1);
    // rotPoint = {100, 100};
    rotPoint.at(0,0) = 100;
    rotPoint.at(1,0) = 100;
    Matrix2D<double> rotMat(2,2);

    std::vector<Matrix2D<double>> points;

    for (int i = 0; i < 4; i++) {
        Matrix2D<double> point(2, 1);
        points.push_back(point);
    }

    double deg = 0.01;    // in rad

    points.at(0) = (40);
    points.at(1).at(0,0) = (40);
    points.at(1).at(1,0) = (160);
    points.at(2) = (160);
    points.at(3).at(0,0) = (160);
    points.at(3).at(1,0) = (40);
        
    for (auto p : points)
        p.print();

    while (window.ProcessMessages()) {
        window.clearScreen(0x000000);
        window.drawPolygon(points, 0x00FFFF);
        window.update();

        Matrix2D<double>::rotate(points, rotPoint, deg);

        if (deg > 2 * M_PI) 
            deg -= 2 * M_PI;

        Sleep(1000 / FPS);
    }
    return 0;
}