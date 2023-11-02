#pragma once

#include <windows.h>

LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window{
public:
    Window();
    Window(const Window&) = delete;
    Window& operator= (const Window&) = delete;
    ~Window();

    bool ProcessMessages();

private:
    HINSTANCE _hInstance;
    HWND _hWnd;
};