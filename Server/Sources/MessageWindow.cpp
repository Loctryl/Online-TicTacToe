#include "Headers/MessageWindow.h"
#include "Headers/ServerRequestManager.h"
#include "Headers/NetManager.h"

HWND MessageWindow::hWnd = NULL;

MessageWindow::MessageWindow()
{
    hInst = GetModuleHandle(0);
    hPrevInstance = 0;
    lpCmdLine = 0;
    nCmdShow = SW_SHOW;
}

bool MessageWindow::InitWindow()
{
    MyRegisterClass();

    // Perform application initialization:
    if (!InitInstance())
    {
        return FALSE;
    }

    return TRUE;
}

BOOL MessageWindow::InitInstance()
{
    bool fullscreen = false;

    hWnd = CreateWindowW(szWindowClass, L"",
        fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW,
        100, 100, 1600, 900,
        nullptr, nullptr, hInst, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    return TRUE;
}

ATOM MessageWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = nullptr;

    return RegisterClassExW(&wcex);
}

HWND& MessageWindow::GetHWND() { return hWnd; }

HINSTANCE& MessageWindow::GetHInstance() { return hInst; }


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_SOCKET:
    {
        SOCKET socket = wParam;
        SOCKET newSocket = INVALID_SOCKET;
        ServerRequestManager* requestManager = ServerRequestManager::GetInstance();// TO DO : A remplacer par RequestManager*, non ?
        string message = "";

        switch (LOWORD(lParam))
        {
        case FD_ACCEPT:
            requestManager->GetNetWork()->AcceptClient(&newSocket);
            NetManager::GetInstance()->CreatePlayer(&socket);
            break;

        case FD_READ:
            message = requestManager->Recieve();
            requestManager->ManageMessage(message);
            break;

        case FD_CLOSE:

            break;

        default:
            break;
        }
    }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
