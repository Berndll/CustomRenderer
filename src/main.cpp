#include <iostream>
#include <math.h>
#include <vector>

#include "../include/utils.hpp"
#include "../include/Window.hpp"

#include "../include/Matrix.hpp"

#define FPS 100 // default = 100

using vec2d = std::vector<std::vector<double>>;
using vec3d = std::vector<std::vector<std::vector<double>>>;

template<typename T>
using vec2 = std::vector<std::vector<T>>;

void draw();

int main() {
    Window window(512, 512);
    
    while (window.ProcessMessages()) {
        window.clearScreen(0x000000);
        window.update();
    }
    return 0;
}