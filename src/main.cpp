#include <iostream>
#include <math.h>
#include <vector>

#include "Window.hpp"

#define FPS 100 // default = 100

int main() {
    Window window;

    std::pair<int, int> rotPoint {100,100};
    Matrix<double> rotMat(2,2);
    // std::vector<std::pair<double, double>> rectangle {{40,40}, {40,160}, {160,160}, {160,40}};

    // Matrix<double> point0(2,1), point1(2,1), point2(2,1), point3(2,1);

    std::vector<Matrix<double>> points;

    for (int i = 0; i < 4; i++) {
        Matrix<double> point(2, 1);
        points.push_back(point);
    }

    double deg = 0.01;    // in rad

    points.at(0) = (40,  40);
    points.at(1).at(0,0) = (40);
    points.at(1).at(1,0) = (160);
    points.at(2) = (160,160);
    points.at(3).at(0,0) = (160);
    points.at(3).at(1,0) = (40);
        
    for (auto p : points)
        p.print();

    while (window.ProcessMessages()) {
        window.clearScreen(0x000000);
        // window.drawPolygon(rectangle, 0x00FF00);
        window.drawPolygon(points, 0x00FFFF);
        window.update();

        rotMat.at(0,0) =  cos(deg);
        rotMat.at(1,0) =  sin(deg);
        rotMat.at(0,1) = -sin(deg);
        rotMat.at(1,1) =  cos(deg);

        for (int i = 0; i < points.size(); ++i) {
            points.at(i).at(0,0) -= rotPoint.first;
            points.at(i).at(1,0) -= rotPoint.second;
        }

        for (int i = 0; i < points.size(); ++i) {
            // std::cout << p.dotProduct(rotMat, p).at(0,0) << std::endl;
            auto p_old = points.at(i);
            // std::cout << p.at(0,0) << " | ";
            points.at(i) = points.at(i).dotProduct(rotMat, p_old);
            // std::cout << p.at(0,0) << "\n";
            // auto t = p.dotProduct(rotMat, p);
        }

        for (int i = 0; i < points.size(); ++i) {
            points.at(i).at(0,0) += rotPoint.first;
            points.at(i).at(1,0) += rotPoint.second;
        }

        if (deg > 360) deg -= 360;

        // for (int i = 0; i < rectangle.size(); ++i) {
        //     rectangle.at(i).first  -= rotPoint.first;
        //     rectangle.at(i).second -= rotPoint.second;
        // }

        // for (int i = 0; i < rectangle.size(); ++i) {
        //     double x_old = rectangle.at(i).first;
        //     double y_old = rectangle.at(i).second;

        //     rectangle.at(i).first  = x_old * cos(deg) - y_old * sin(deg);
        //     rectangle.at(i).second = x_old * sin(deg) + y_old * cos(deg); 
        // }
        // for (int i = 0; i < rectangle.size(); ++i) {
        //     rectangle.at(i).first  += rotPoint.first;
        //     rectangle.at(i).second += rotPoint.second;
        // }

        // if (deg > 360) deg -= 360;

        // window.drawLine(0, 0, window.getWidth() - 1, window.getHeight() - 1, 0xFF0000);

        Sleep(1000 / FPS);
    }
    return 0;
}