#include <iostream>
#include <math.h>
#include <vector>

#include "Matrix.hpp"
#include "Window.hpp"

// float sine(float x)   { return (16 * x * (PI - x)) / (5 * PI_SQUARED - 4 * x * (PI - x)); } // Bhāskara I approximation
// float cosine(float x) { return sine(x + PI_HALF); }

int main() {
    Window window;

    std::pair<int, int> rotPoint {100,100};
    // Matrix<float> rotMat(2,2);
    std::vector<std::pair<float, float>> rectangle {{40,40}, {40,160}, {160,160}, {160,40}};

    float deg = 0;    // rad

    while (window.ProcessMessages()) {
        window.clearScreen(0x000000);
        window.drawPolygon(rectangle, 0x00FF00);
        window.update();

        for (int i = 0; i < rectangle.size(); ++i) {
            rectangle.at(i).first  -= rotPoint.first;
            rectangle.at(i).second -= rotPoint.second;
        }

        for (int i = 0; i < rectangle.size(); ++i) {
            float x_old = rectangle.at(i).first;
            float y_old = rectangle.at(i).second;

            rectangle.at(i).first  = x_old * cos(deg) - y_old * sin(deg);
            rectangle.at(i).second = x_old * sin(deg) + y_old * cos(deg); 

            std::cout << "x " << rectangle.at(i).first << " | y" << rectangle.at(i).second << "\n";
        }
        std::cout << "\n" << std::endl;


        // rotMat.data.at(0).at(0) =  cos(deg);
        // rotMat.data.at(1).at(0) =  sin(deg);
        // rotMat.data.at(0).at(1) = -sin(deg);
        // rotMat.data.at(1).at(1) =  cos(deg);


        for (int i = 0; i < rectangle.size(); ++i) {
            rectangle.at(i).first  += rotPoint.first;
            rectangle.at(i).second += rotPoint.second;
        }

        if (deg > 360) deg -= 360;
        deg += 0.0001;


        // window.drawLine(0, 0, window.getWidth() - 1, window.getHeight() - 1, 0xFF0000);

        Sleep(10); // Lower FPS
    }
    return 0;
}