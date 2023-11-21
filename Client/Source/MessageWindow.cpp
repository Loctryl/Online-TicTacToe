#include "Headers/MessageWindow.h"
#include "Headers/ClientRequestManager.h"

HWND MessageWindow::hWnd = NULL;

MessageWindow::MessageWindow()
{
    hInst = GetModuleHandle(0);
    hPrevInstance = 0;
    lpCmdLine = 0;
    nCmdShow = SW_SHOW;
}

bool MessageWindow::InitWindow(CRITICAL_SECTION* mutex)
{
    MyRegisterClass();

    // Perform application initialization:
    if (!InitInstance(mutex))
    {
        return FALSE;
    }

    return TRUE;
}

BOOL MessageWindow::InitInstance(CRITICAL_SECTION* mutex)
{
    bool fullscreen = false;

    hWnd = CreateWindowW(szWindowClass, L"",
        fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW,
        100, 100, 1600, 900,
        nullptr, nullptr, hInst, mutex);

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
    case WM_CREATE:
    {
        // Sauvegarde le mutex passé dans CreateWindow
        LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
        break;

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
        string message = "";

        CRITICAL_SECTION* mutex = reinterpret_cast<CRITICAL_SECTION*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));// Récupération du mutex passé dans CreateWindow
        EnterCriticalSection(mutex);// pour bloquer un bloc d'instructions

        ClientRequestManager* requestManager = ClientRequestManager::GetInstance();

        switch (lParam)
        {
        case FD_READ:
            message = requestManager->Recieve(&socket);
            if (!message.empty())
                requestManager->ManageMessage(message);
            break;

        case FD_CLOSE:
            break;
            requestManager->GetNetWork()->CloseSocket(socket);
        default:
            break;
        }

        LeaveCriticalSection(mutex);// pour libérer le bloc
    }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
