#include <iostream>
#include <math.h>
#include <vector>

#include "../include/utils.hpp"
#include "../include/Window.hpp"

#define FPS 100 // default = 100

using vec2d = std::vector<std::vector<double>>;
using vec3d = std::vector<std::vector<std::vector<double>>>;

template<typename T>
using vec2T = std::vector<std::vector<T>>;

void draw();

int main() {
    std::vector<Matrix2D<double>> points;
    // std::cout << "test";
    points = readFilePoints("input/object.txt");

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

    for (auto p : points)
        p.print();

    static double it = 0;
    while (window.ProcessMessages()) {
        window.clearScreen(0x000000);

        // window.drawPixel(0,0, 0xFFFFFF);


        window.drawPolygon(points, 0xFFFFFF);
        // window.drawPolygon(projectedPoints, 0xFFFFFF);

        // theta.at(0,0) += 0.001;
        // theta.at(1,0) += 0.001;
        // theta.at(2,0) += 0.001;

        // for (int i = 0; i < projectedPoints.size(); ++i)
        //     for (int j = 0; j < projectedPoints.size(); ++j) {
        //         window.drawLine(
        //             projectedPoints.at(i).at(0,0),
        //             projectedPoints.at(i).at(1,0),
        //             projectedPoints.at(j).at(0,0),
        //             projectedPoints.at(j).at(1,0),
        //             0x8FFFFF
        //         );
        //     }

        // for (int i = 0; i < transformedPoints.size(); ++i) {
        //     transformedPoints.at(i) = points.at(i).transform(camera, theta);
        //     projectedPoints.at(i) = transformedPoints.at(i);
        // }
        
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