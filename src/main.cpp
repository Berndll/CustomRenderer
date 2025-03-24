#include <iostream>
#include <math.h>
#include <vector>

#include "../include/Window.hpp"

// #include "../include/utils.hpp"
#include "../include/Matrix.hpp"
// #include "../include/Vector.hpp"

#define FPS 100 // default = 100

using vec2d = std::vector<std::vector<double>>;
using vec3d = std::vector<std::vector<std::vector<double>>>;

template<typename T>
using vec2 = std::vector<std::vector<T>>;

void draw(Window& window) {

    window.drawLine(100, 100, 0, 0, 0xFFFFFF);
}

int main() {
    Window window(512, 512);
    
    Matrix<double> point_a(1, 3); // to be projected
    Matrix<double> camera(1, 3); // the camera's position
    Matrix<double> display(1, 3); // the display's position
    Matrix<double> point_d(1, 3); // A with respect to the camera's position
   
    std::vector<Matrix<double>> points;
    std::vector<Matrix<double>> points_translated;
    std::vector<Matrix<double>> points_projected;

    for (int i = 0; i < 8; ++i) {
        points.push_back(Matrix<double>(1, 3));
        points_translated.push_back(Matrix<double>(1, 3));
        points_projected.push_back(Matrix<double>(1, 2));
    }

    points.at(0) = { {0, 0, 1} };
    points.at(1) = { {0, 1, 1} };
    points.at(2) = { {1, 0, 1} };
    points.at(3) = { {1, 1, 1} };

    points.at(4) = { {0, 0.5, 2} };
    points.at(5) = { {0, 1.5, 2} };
    points.at(6) = { {1, 0.5, 2} };
    points.at(7) = { {1, 1.5, 2} };

    // for (auto point : points_translated)
    //     std::cout << point.getSize().cols << " " << point.getSize().rows << " | ";
    // std::cout << std::endl;
    // for (auto point : points)
    //     std::cout << point.getSize().cols << " " << point.getSize().rows << " | ";
    // std::cout << std::endl;

    camera  = { { 0, 0, 0 } };
    display = { { 0, 0, 1 } };

    

    // std::cout << "HAHAHA" << std::endl;

    // point_d.print();
    
    while (window.ProcessMessages()) {
        window.clearScreen(0x000000);
        
        for (int i = 0; i < points.size(); ++i) {
            points_translated.at(i) = points.at(i) - camera;
            // points_translated.at(i).print();
        }
    
        for (int i = 0; i < points.size(); ++i) {
            points_projected.at(i).at(0, 0) =
                (display.at(0, 2) / points_translated.at(i).at(0, 2)) * // e_z / d_z
                points_translated.at(i).at(0, 0) + // * d_x
                display.at(0, 0); // + e_x
    
            points_projected.at(i).at(0, 1) =
                (display.at(0, 2) / points_translated.at(i).at(0, 2)) * // e_z / d_z
                points_translated.at(i).at(0, 1) + // * d_y
                display.at(0, 1); // + e_y
        }

        for (auto point : points_projected) {
            window.drawPixel(point.at(0, 0) * 100, point.at(0, 1) * 100, 0xFFFFFF);
        }

        // draw(window);
        window.update();

        // for (int i = 0; i < 8; ++i)
        //     points.at(i).at(0, 2) += 0.001;

        // camera.at(0, 0);
        camera.at(0, 1) -= 0.0001;
        // camera.at(0, 2) -= 0.0001;
    }
    return 0;
}