#pragma once

// https://www.youtube.com/watch?v=Kx5CN-V6FvQ
// https://www.youtube.com/watch?v=vEFpaJdKcYU

#include <gdiplus.h>
#include <windows.h>

LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window{
public:
    Window();
    Window(const Window&) = delete;
    Window& operator= (const Window&) = delete;
    ~Window();

    bool ProcessMessages();

    void draw();

    const HWND getWindow() { return _hWnd; }

    BITMAPINFO getBitmapInfo() { return _bitmap_info; }
    long getClientWidth()   { return _clientWidth;  }
    long getClientHeight()  { return _clientHeight; }
    PVOID getMemory()  { return _memory; }

    BITMAPINFO _bitmap_info;

private:
    HINSTANCE _hInstance;
    HWND _hWnd;

    long _width = 640, _height = 480;
    long _clientWidth, _clientHeight;
    PVOID _memory;

    void bitmapinfo();
};