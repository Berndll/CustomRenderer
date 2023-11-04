#include <iostream>
#include "Window.hpp"

int main() {
    Window window;

    while (window.ProcessMessages()) {
        window.drawLine(0, 0, 639, 479, 0xFF0000);
        window.drawPixel(10, 10, 0xFF0000);
        window.drawRect(0, 0, 200, 200, 0x0000FF);

        window.update();
        Sleep(10); // Lower FPS
    }

    return 0;
}