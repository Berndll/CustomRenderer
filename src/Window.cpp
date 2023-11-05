#include "Window.hpp"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static bool size_changed = true;
    if ( uMsg == WM_SIZE ) {
        size_changed = true;
    } else if ( size_changed ) {
        PostMessage( hWnd, WM_SIZE, wParam, lParam );
        size_changed = false;
    }

    switch (uMsg) {
    case WM_CLOSE: // Close-Button
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window() : _hInstance(GetModuleHandle(nullptr)) {
    std::cout << "Creating Window\n";

    const auto CLASS_NAME = L"My Window Class";

    WNDCLASS wndClass = {};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance = _hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    RegisterClass(&wndClass);

    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + _width;
    rect.bottom = rect.top + _height;

    _clientWidth  = rect.right  - rect.left;
    _clientHeight = rect.bottom - rect.top;

    // Allocate Memory
    _memory = VirtualAlloc(
        0,
        _clientWidth * _clientHeight * sizeof(uint32_t), 
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );

    // Bitmap info
    bitmapinfo();

    AdjustWindowRect(&rect, style, false);  // Adjusts to use canvas size not window size

    _hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Renderer",
        style,
        rect.left,
        rect.top,
        _clientWidth,
        _clientHeight,
        NULL,
        NULL,
        _hInstance,
        NULL
    );

    // RECT rect2;
    // GetClientRect( _hWnd, &rect2 );
    // auto w = rect2.right - rect2.left;
    // std::cout << "w: " << w << " | _width: " << _width << std::endl;
    
    ShowWindow(_hWnd, SW_SHOW);
}

Window::~Window() {
    const wchar_t* CLASS_NAME = L"My Window Class";

    UnregisterClass(CLASS_NAME, _hInstance);

    std::cout << "Closing Window\n";
}

bool Window::ProcessMessages() {
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
        switch (msg.message) {
        case WM_QUIT: 
            return false;
        case WM_SIZE:
        break;
            std::cout << "Changed window size\n";

            RECT rect;
            GetClientRect(_hWnd, &rect);
            _clientWidth = rect.right - rect.left;
            _clientHeight = rect.bottom - rect.top;

            if (_memory)
                VirtualFree(_memory, 0, MEM_RELEASE);

            _memory = VirtualAlloc(
                0,
                _clientWidth * _clientHeight * sizeof(uint32_t), 
                MEM_RESERVE | MEM_COMMIT,
                PAGE_READWRITE
            );

            bitmapinfo();
            break;

        default:
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return true;
}

void Window::bitmapinfo() {
    _bitmap_info.bmiHeader.biSize = sizeof(_bitmap_info.bmiHeader);
    _bitmap_info.bmiHeader.biWidth = _clientWidth;
    // Negative biHeight makes top left as the coordinate system origin. Otherwise it's bottom left.
    _bitmap_info.bmiHeader.biHeight = -_clientHeight;
    _bitmap_info.bmiHeader.biPlanes = 1;
    _bitmap_info.bmiHeader.biBitCount = 32;
    _bitmap_info.bmiHeader.biCompression = BI_RGB;
}

void Window::update() {
    StretchDIBits(
        GetDC(_hWnd),    // draw on this window
        0,      // start
        0,      // start
        _clientWidth,    // size
        _clientHeight,   // size
        0, 
        0, 
        _clientWidth, 
        _clientHeight, 
        _memory, // pixel data
        &_bitmap_info, // how to interpret memory
        DIB_RGB_COLORS, 
        SRCCOPY
    );
}

void Window::clearScreen(uint32_t color) {
    uint32_t* pixel = (uint32_t*)_memory;
    for (int i = 0; i < _width * _height; ++i)
        pixel[i] = color;
}

void Window::drawPixel(int x, int y, uint32_t color) {
    uint32_t* pixel = (uint32_t*)_memory;
    pixel[_clientWidth * y + x] = color;
}

void Window::drawLine(int x0, int y0, int x1, int y1, uint32_t color) {
    auto abs = [](int n) { return (n > 0) ? n : -n; };

    int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (1) {
        drawPixel(x0, y0, color);
        if (x0 == x1 && y1 == y0) 
            break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

void Window::drawRect(int x0, int y0, int x1, int y1, uint32_t color) {
    drawLine(x0, y0, x0, y1, color);
    drawLine(x0, y0, x1, y0, color);
    drawLine(x0, y1, x1, y1, color);
    drawLine(x1, y0, x1, y1, color);
}
/*
void Window::drawPolygon(std::vector<std::pair<int, int>> points, uint32_t color) {
    for (int i = 0; i < points.size() - 1; ++i)
        drawLine(
            points.at(i).first,   points.at(i).second, 
            points.at(i+1).first, points.at(i+1).second, 
            color
        );
    drawLine(
        points.at(0).first,  points.at(0).second, 
        points.back().first, points.back().second, 
        color
    );
}

void Window::drawPolygon(std::vector<std::pair<double, double>> points, uint32_t color) {
    for (int i = 0; i < points.size() - 1; ++i)
        drawLine(
            points.at(i).first,   points.at(i).second, 
            points.at(i+1).first, points.at(i+1).second, 
            color
        );
    drawLine(
        points.at(0).first,  points.at(0).second, 
        points.back().first, points.back().second, 
        color
    );
}
*/
void Window::drawPolygon(std::vector<Matrix2D<double>> points, uint32_t color) {
    for (int i = 0; i < points.size() - 1; ++i) {
        drawLine(
            points.at(i).at(0,0),   points.at(i).at(1,0),
            points.at(i+1).at(0,0), points.at(i+1).at(1,0),
            color
        );
    }
    drawLine(
        points.at(0).at(0,0),  points.at(0).at(1,0),
        points.back().at(0,0), points.back().at(1,0),
        color
    );
}