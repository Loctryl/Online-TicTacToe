#include "MessageWindow.h"

HWND Window::hWnd = NULL;

Window::Window()
{
    hInst = GetModuleHandle(0);
    hPrevInstance = 0;
    lpCmdLine = 0;
    nCmdShow = SW_SHOW;
}

bool Window::InitWindow()
{
    MyRegisterClass();

    // Perform application initialization:
    if (!InitInstance())
    {
        return FALSE;
    }

    return TRUE;
}

BOOL Window::InitInstance()
{
    bool fullscreen = false;

    hWnd = CreateWindowW(L"", L"",
        fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW,
        100, 100, 1600, 900,
        nullptr, nullptr, hInst, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

ATOM Window::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInst;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;

    return RegisterClassExW(&wcex);
}

HWND& Window::GetHWND() { return hWnd; }

HINSTANCE& Window::GetHInstance() { return hInst; }


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
