#include <iostream>
#include "Window.hpp"

int main() {
    std::cout << "Creating Window\n";

    Window* pWindow = new Window();

    bool running = true;

    HDC hdc = GetDC(pWindow->getWindow());

    uint32_t* pixel = (uint32_t*)pWindow->getMemory();
        for (int i = 0; i < 640 * 480 - 100; ++i)
        pixel[i] = 0x0000FF;
    pixel = (uint32_t*)pWindow->getMemory();

    while (running) {
        if (!pWindow->ProcessMessages()) {
            std::cout << "Closing Window\n";
            running = false;
        }

        /*
        // for (int i = 0; i < width * height; ++i) {
        //     if (val) pixel[i] = 0x0000FF;
        //     else     pixel[i] = 0xFF0000;

        //     val = i%2;
        // }

        // Copy from memory to window
        */
        pixel = (uint32_t*)pWindow->getMemory();
        for (int i = 0; i < 640 * 480; ++i) {
            pixel[i] = 0xFF0000;
        }
        
        pWindow->draw();

        Sleep(10); // Lower FPS
    }

    delete pWindow;

    return 0;
}