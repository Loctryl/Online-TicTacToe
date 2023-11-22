#include "Headers/MessageWindow.h"
#include "Headers/ServerRequestManager.h"
#include "Headers/ServApp.h"
#include "Headers/NetManager.h"

HWND MessageWindow::hWnd = NULL;

MessageWindow::MessageWindow(ServApp* serverApp)
{
	hInst = GetModuleHandle(0);
	hPrevInstance = 0;
	lpCmdLine = 0;
	nCmdShow = SW_SHOW;
	mServerApp = serverApp;
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
		nullptr, nullptr, hInst, this);

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

LRESULT MessageWindow::WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	SOCKET socket = wParam;
	SOCKET* newSocket = new SOCKET(INVALID_SOCKET);
	string response = "";

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SOCKET:
	{
		switch (LOWORD(lParam))
		{
		case FD_ACCEPT:
			mServerApp->EnterMutex();

			ServerRequestManager* requestManager = ServerRequestManager::GetInstance();
			requestManager->GetNetWork()->AcceptClient(newSocket);

			mServerApp->LeaveMutex();

			NetManager::GetInstance()->CreatePlayer(newSocket);
			break;

		case FD_READ:
			mServerApp->EnterMutex();

			ServerRequestManager* requestManager = ServerRequestManager::GetInstance();
			response = requestManager->Recieve(&socket);

			mServerApp->LeaveMutex();

			if (!response.empty())
			{
				mServerApp->EnterMutex();

				requestManager->ManageMessage(response, &socket);

				mServerApp->LeaveMutex();
			}
			break;

		case FD_CLOSE:
			mServerApp->EnterMutex();

			ServerRequestManager* requestManager = ServerRequestManager::GetInstance();
			requestManager->GetNetWork()->CloseSocket(socket);

			mServerApp->LeaveMutex();
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

LRESULT CALLBACK MessageWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		// Sauvegarde du l'instance de MessageWindow dans la window
		LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));

		return DefWindowProc(hWnd, message, wParam, lParam);

	default:
		MessageWindow* messageWindow = reinterpret_cast<MessageWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return messageWindow->WndInstanceProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
