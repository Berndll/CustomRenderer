#include <iostream>
#include <math.h>
#include <vector>

#include "../include/utils.hpp"
#include "../include/Window.hpp"

#define FPS 100 // default = 100

using vec2d = std::vector<std::vector<double>>;
using vec3d = std::vector<std::vector<std::vector<double>>>;

template<typename T>
using vec2 = std::vector<std::vector<T>>;

void draw();

int main() {
    std::vector<Matrix2D<double>> points;
    points = readFilePoints("input/object.txt");

    // for (auto p : points)
    //     p.print();

    std::vector<Matrix2D<double>> temp2;

    Window window(1000, 800);

    Matrix2D<double> rotPoint(readFilePoints("input/rotPoint.txt").at(0));

    double deg = 0.01;    // in rad

    Matrix2D<double> camera(readFilePoints("input/camera.txt").at(0));
    Matrix2D<double> theta(readFilePoints("input/theta.txt").at(0));

    std::vector<Matrix2D<double>> transformedPoints;
    std::vector<Matrix2D<double>> projectedPoints;

    for (int i = 0; i < points.size(); ++i) {
        transformedPoints.push_back(points.at(i).transform(camera, theta));
        projectedPoints.push_back(transformedPoints.at(i));
    }

    Matrix2D<double> temp3(2,1);
    temp3.at(0,0) = 0;
    temp3.at(1,0) = 0;
    // temp3.print();

    for (int i = 0; i < 8; ++i)
        temp2.push_back(temp3);

    // temp2.resize(8);
    // for (auto a : temp2)
    //     a.resize(2,1);

    // for (auto p : temp2)
    //     p.print();

    // static double it = 0;
    Matrix2D<double> temp(readFilePoints("input/plane.txt").at(0));
    // temp.at(2,0) = 75;
    static double it = 0.1;

    while (window.ProcessMessages()) {
        window.clearScreen(0x000000);

        // window.drawPixel(0,0, 0xFFFFFF);

        // window.drawPolygon(points, 0xFFFFFF);

        // window.drawPolygon(projectedPoints, 0xFFFFFF);
        // camera.at(1,0) = 100;

        // temp.at(2,0) -= 0.1;
        
        // temp.at(0,0) += 0.01;
        // temp.at(1,0) += 0.01;

        // static double angle = 180.0;
        it += 0.001;


        // theta.at(0,0) = -M_PI_4;
        // theta.at(1,0) = M_PI_4;
        // theta.at(2,0) = M_PI_4;
        // theta.at(2,0) += 0.01;

        // temp.at(1,0) += 0.5;

        double aspectRatio = 16 / 9.0;
        double horizontalFOV = 60 * M_PI / 180;
        double verticalFOV = 2 * atan(tan(horizontalFOV / (2 * aspectRatio)));
        
        temp.at(2,0) = camera.at(2,0) + (8 / tan(horizontalFOV / (2 * 1)));

        // std::cout << horizontalFOV;

        // camera.at(1,0) += 0.05;

        for (int i = 0; i < projectedPoints.size(); ++i)
            for (int j = 0; j < projectedPoints.size(); ++j) {
                // window.drawLine(
                //     projectedPoints.at(i).at(0,0),
                //     projectedPoints.at(i).at(1,0),
                //     projectedPoints.at(j).at(0,0),
                //     projectedPoints.at(j).at(1,0),
                //     0x8FFFFF
                // );
                window.drawLine(
                    temp2.at(i).at(0,0),
                    temp2.at(i).at(1,0),
                    temp2.at(j).at(0,0),
                    temp2.at(j).at(1,0),
                    0xFFFFFF
                );
            }


        for (int i = 0; i < transformedPoints.size(); ++i) {
            transformedPoints.at(i) = points.at(i).transform(camera, theta);

            // std::cout << 
            //     projectedPoints.size() << " | " << 
            //     transformedPoints.size() << "\n";


            temp2.at(i) = 
                projectedPoints.at(i).project(transformedPoints.at(i), temp);
            // std::cout << temp2.at(0).at(0,0);

            // temp2.at(i).print();
        }


        window.update();
    }
    return 0;
}

void draw() {
            // for (int x = 0; x < window.getWidth(); ++x)
        //     for (int y = 0; y < window.getHeight(); ++y)
/*                 window.drawPixel(x, y, (
                    sin(x * 2 * M_PI / 1000) * cos(x * 2 * M_PI / 1000) * 
                    sin(x * 2 * M_PI / 1000) *
                    sin(y * 2 * M_PI / 1000) * cos(y * 2 * M_PI / 1000) *
                    sin(y * 2 * M_PI / 1000) *
                    0xFFFFFF));
 */                // window.drawPixel(x, y, 10000 * log(x) / log(y));
                // window.drawPixel(x, y, uint32_t(x*y - x * x));

}