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
    Vector<double> vec("input/camera.txt");
    // vec.print();

    // vec.strSplit("20,10,10", ',');

    return 0;

    std::vector<Matrix2D<double>> points;
    points = readFilePoints("input/object.txt");

    // std::vector<Matrix2D<double>> temp2;

    Window window(1000, 800);

    Matrix2D<double> rotPoint(readFilePoints("input/rotPoint.txt").at(0));

    double deg = 0.01;    // in rad

    Matrix2D<double> camera(readFilePoints("input/camera.txt").at(0));
    Matrix2D<double> theta(readFilePoints("input/theta.txt").at(0));
    
    /*
    std::vector<Matrix2D<double>> transformedPoints;
    std::vector<Matrix2D<double>> projectedPoints;

    for (int i = 0; i < points.size(); ++i) {
        transformedPoints.push_back(points.at(i).transform(camera, theta));
        projectedPoints.push_back(transformedPoints.at(i));
    }

    Matrix2D<double> temp3(2,1);
    temp3.at(0,0) = 0;
    temp3.at(1,0) = 0;

    for (int i = 0; i < 8; ++i)
        temp2.push_back(temp3);

    // Matrix2D<double> temp(readFilePoints("input/plane.txt").at(0));*/
    
    while (window.ProcessMessages()) {
        window.clearScreen(0x000000);



        /*
        // window.drawPixel(0,0, 0xFFFFFF);

        // window.drawPolygon(points, 0xFFFFFF);

        // window.drawPolygon(projectedPoints, 0xFFFFFF);
        
        double aspectRatio = 16 / 9.0;
        double horizontalFOV = 60 * M_PI / 180;
        double verticalFOV = 2 * atan(tan(horizontalFOV / (2 * aspectRatio)));
        
        temp.at(2,0) = camera.at(2,0) + (8 / tan(horizontalFOV / (2 * 1)));

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
        uint32_t color = 0xFFFFFF;
        window.drawLine(temp2.at(0).at(0,0), temp2.at(0).at(1,0), temp2.at(1).at(0,0), temp2.at(1).at(1,0), color);
        window.drawLine(temp2.at(0).at(0,0), temp2.at(0).at(1,0), temp2.at(2).at(0,0), temp2.at(2).at(1,0), color);
        window.drawLine(temp2.at(0).at(0,0), temp2.at(0).at(1,0), temp2.at(4).at(0,0), temp2.at(4).at(1,0), color);
        window.drawLine(temp2.at(1).at(0,0), temp2.at(1).at(1,0), temp2.at(5).at(0,0), temp2.at(5).at(1,0), color);
        window.drawLine(temp2.at(1).at(0,0), temp2.at(1).at(1,0), temp2.at(3).at(0,0), temp2.at(3).at(1,0), color);
        window.drawLine(temp2.at(2).at(0,0), temp2.at(2).at(1,0), temp2.at(6).at(0,0), temp2.at(6).at(1,0), color);
        window.drawLine(temp2.at(3).at(0,0), temp2.at(3).at(1,0), temp2.at(2).at(0,0), temp2.at(2).at(1,0), color);
        window.drawLine(temp2.at(3).at(0,0), temp2.at(3).at(1,0), temp2.at(7).at(0,0), temp2.at(7).at(1,0), color);
        window.drawLine(temp2.at(4).at(0,0), temp2.at(4).at(1,0), temp2.at(5).at(0,0), temp2.at(5).at(1,0), color);
        window.drawLine(temp2.at(4).at(0,0), temp2.at(4).at(1,0), temp2.at(6).at(0,0), temp2.at(6).at(1,0), color);
        window.drawLine(temp2.at(5).at(0,0), temp2.at(5).at(1,0), temp2.at(7).at(0,0), temp2.at(7).at(1,0), color);
        window.drawLine(temp2.at(6).at(0,0), temp2.at(6).at(1,0), temp2.at(7).at(0,0), temp2.at(7).at(1,0), color); 

        for (int i = 0; i < transformedPoints.size(); ++i) {
            transformedPoints.at(i) = points.at(i).transform(camera, theta);

            // std::cout << transformedPoints.at(0).at(0,0) << " | " << transformedPoints.at(0).at(1,0) << std::endl;
            // std::cout << projectedPoints.at(0).at(0,0) << " | " << projectedPoints.at(0).at(1,0) << std::endl;


            temp2.at(i) = projectedPoints.at(i).project(transformedPoints.at(i), temp);
            std::cout << temp2.at(0).at(0,0) << " | " << temp2.at(0).at(1,0) << std::endl;

            // temp2.at(i).print();
        }*/
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