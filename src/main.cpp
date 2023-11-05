#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>

#include "Window.hpp"

#define FPS 100 // default = 100

int main() {
    std::fstream input;
    input.open("input/object.txt", std::ios::in);

    if (input.is_open()) {
        std::string str;

        while (std::getline(input, str)) {
            // for (int i = 0; i < str.size(); ++i) {
            //     if (str.at(i) == ',') {
            //         std::cout << "\n";
            //     }
            //     std::cout << str.at(i);
            // }



            // int it = 0, num;
            // while (num != std::string::npos) {
            //     num = static_cast<int>(temp.find(","));
            //     for (int i = 0; i < num; ++i)
            //         std::cout << temp.at(i) << "\n";
            //         // std::cout << num << "\n";
            //     it = 1;
            // }
        }
        std::cout << "\n" << std::endl;
        input.close();
    }

    return 0;

    Window window;

    // Matrix3D<double> threeD (3,3,3);
    // threeD.print();

    // return 0;

    Matrix2D<double> rotPoint(2,1);
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

    while (window.ProcessMessages()) {
        window.clearScreen(0x000000);
        window.drawPolygon(points, 0x00FFFF);
        window.update();

        for (auto &p : points)
            p.rotate(rotPoint, deg);

        if (deg >= 2 * M_PI) 
            deg -= 2 * M_PI;

        Sleep(1000 / FPS);
    }
    return 0;
}