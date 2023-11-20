#include "Headers/MessageWindow.h"
#include "Headers/ServerRequestManager.h"
#include "Headers/NetManager.h"
#include <iostream>
#include <sstream>
#include <fstream>

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

void ReadWebserverFile() {
    std::ifstream webserver("webserver.html");
    std::stringstream buffer;

    if (webserver.is_open()) {
        buffer << webserver.rdbuf();
        std::string content = buffer.str();
        std::cout << "Content of webserver.html:\n" << content << std::endl;
        std::cout << "Length of content: " << content.length() << std::endl;
    }
    else {
        std::cout << "Failed to open webserver.html" << std::endl;
    }
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SOCKET socket = wParam;
    SOCKET newSocket = INVALID_SOCKET;
    ServerRequestManager* requestManager = ServerRequestManager::GetInstance();// TO DO : A remplacer par RequestManager*, non ?
    string response = "";
    std::ifstream webserver("./Sources/webserver.html", std::ios::binary | std::ios::ate);
    std::stringstream webserverbuffer;
    std::string webserverstring;
    size_t webserverlength;

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

        switch (LOWORD(lParam))
        {
        case FD_ACCEPT:
            requestManager->GetNetWork()->AcceptClient(&newSocket);
            NetManager::GetInstance()->CreatePlayer(&socket);
            break;

        case FD_READ:
            response = requestManager->Recieve(&socket);
            if (!response.empty())
                requestManager->ManageMessage(response, &socket);
            break;

        case FD_CLOSE:
            requestManager->GetNetWork()->CloseSocket(socket);
            break;
        default:
            break;
        }
    }
        break;
    case WM_WEBSOCKET:
    {
        switch (LOWORD(lParam))
        {
        case FD_ACCEPT:
            requestManager->GetNetWork()->AcceptWebClient(&newSocket);
            webserver.seekg(0, std::ios::beg); // Move file pointer to the beginning
            webserverbuffer << webserver.rdbuf();
            webserverstring = webserverbuffer.str();
            webserverlength = webserverstring.length();
            response = "HTTP/1.1 200 OK\r\nServer: TikTakToeHost\r\nContent-Length: " + std::to_string(webserverlength) + "\r\nContent-Type: text/html\r\n\r\n" + webserverstring;
            if (!requestManager->SendToWeb(response, &newSocket))
                return 1;
            //requestManager->GetNetWork()->CloseSocket(newSocket);
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
