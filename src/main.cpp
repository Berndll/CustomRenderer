#include <iostream>
#include "Window.hpp"

int main() {
    std::cout << "Creating Window\n";

    Window* pWindow = new Window();

    bool running = true;

    HDC hdc = GetDC(pWindow->getWindow());

    // Allocate memory.
    RECT Rect;
    GetClientRect(pWindow->getWindow(), &Rect);
    auto ClientWidth = Rect.right - Rect.left;
    auto ClientHeight = Rect.bottom - Rect.top;

    auto memory = VirtualAlloc(
        0,
        ClientWidth * ClientHeight * 4, 
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );

    // Create BITMAPINFO struct for StretchDIBits().
    BITMAPINFO BitmapInfo;
    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = ClientWidth;
    // Negative biHeight makes top left as the coordinate system origin. Otherwise it's bottom left.
    BitmapInfo.bmiHeader.biHeight = ClientHeight;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;

    uint32_t* pixel = (uint32_t*)memory;
        for (int i = 0; i < 640 * 480 - 100; ++i)
        pixel[i] = 0x0000FF;
    pixel = (uint32_t*)memory;

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
        // pixel = (uint32_t*)memory;

        // Copy from memory to window

        // pWindow->update();
        */
        
        StretchDIBits(
            hdc,    // draw on this window
            0,      // start
            0,      // start
            ClientWidth,    // size
            ClientHeight,   // size
            0, 
            0, 
            ClientWidth, 
            ClientHeight, 
            memory, // pixel data
            &BitmapInfo, // how to interpret memory
            DIB_RGB_COLORS, 
            SRCCOPY
        );


        Sleep(10); // Lower FPS
    }

    delete pWindow;

    return 0;
}