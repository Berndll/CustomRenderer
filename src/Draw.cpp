#include "../include/Draw.hpp"

Draw::Draw() {}

Draw::Draw(HWND hwnd, long clientWidth, long clientHeight) : _hwnd(hwnd) {
    _hdc = GetDC(_hwnd);

    // _memory = VirtualAlloc(
    //     0,  // Color
    //     _width * _height * sizeof(uint32_t),
    //     MEM_RESERVE | MEM_COMMIT,
    //     PAGE_READWRITE
    // );

    // _pixel = (uint32_t*)_memory;

    /*
    // Create bitmap info struct for StretchDIBits
    _bitmap_info.bmiHeader.biSize = sizeof(_bitmap_info.bmiHeader);
    _bitmap_info.bmiHeader.biWidth = clientWidth;
    // Negative biHeight makes top left as the coordinate system origin. Otherwise it's bottom left.
    _bitmap_info.bmiHeader.biHeight = clientHeight;
    _bitmap_info.bmiHeader.biPlanes = 1;
    _bitmap_info.bmiHeader.biBitCount = 32;
    _bitmap_info.bmiHeader.biCompression = BI_RGB;*/
}

void Draw::update() {
    StretchDIBits(
        _hdc,
        0,
        0,
        _width,
        _height,
        0,
        0,
        _width,
        _height,
        _memory,
        &_bitmap_info,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}