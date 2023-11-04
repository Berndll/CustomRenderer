#pragma once

#include <windows.h>

#define uint32_t unsigned int

class Draw {
public:
    Draw();
    Draw(HWND hwnd, long clientWidth, long clientHeight);
    void update();
    PVOID _memory;
    uint32_t* _pixel;

    auto getMemory() { return _memory; }

// private:
    HDC _hdc;
    HWND _hwnd;

    RECT _rect;
    BITMAPINFO _bitmap_info;

    long _width, _height;
};

void drawPoint();
