#pragma once

// https://www.youtube.com/watch?v=Kx5CN-V6FvQ
// https://www.youtube.com/watch?v=vEFpaJdKcYU

#include <iostream>
#include <vector>

#include <gdiplus.h>
#include <windows.h>

#include "Matrix3D.hpp"
#include "Matrix.hpp"

LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window{
public:
    Window(int width, int height);
    Window(const Window&) = delete;
    Window& operator= (const Window&) = delete;
    ~Window();

    // static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    bool ProcessMessages();

    void update();

    int getWidth() { return _width;  }
    int getHeight() { return _height; }
    PVOID getMemory()  { return _memory; }

    void clearScreen(uint32_t color);
    void drawPixel(int x, int y, uint32_t color);
    void drawPixel(Vector<double> point, uint32_t color);
    void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
    template<typename T>
    void drawLine(Vector<T> p1, Vector<T> p2, uint32_t color);
    void drawRect(int x0, int y0, int x1, int y1, uint32_t color);
    void drawPolygon(std::vector<Matrix2D<double>> points, uint32_t color);
    void drawPolygon(Matrix<double> points, uint32_t color);

private:
    HINSTANCE _hInstance;
    HWND _hWnd;
    HDC _hdc;
    BITMAPINFO _bitmap_info;
    PVOID _memory = nullptr;

    int _width = 640, _height = 480;
    long _clientWidth, _clientHeight;

    void bitmapinfo();
};