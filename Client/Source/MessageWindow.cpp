#include "Headers/MessageWindow.h"
#include "Headers/ClientRequestManager.h"
#include "Headers/ClientApp.h"

HWND MessageWindow::hWnd = NULL;

MessageWindow::MessageWindow(ClientApp* clientApp)
{
	hInst = GetModuleHandle(0);
	hPrevInstance = 0;
	lpCmdLine = 0;
	nCmdShow = SW_SHOW;
	mClientApp = clientApp;
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
	hWnd = CreateWindowW(szWindowClass, L"",
		WS_OVERLAPPEDWINDOW,
		0, 0, 120, 80,
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



LRESULT MessageWindow::WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SOCKET:
	{
		SOCKET socket = wParam;
		string message = "";

		mClientApp->EnterMutex();

		ClientRequestManager* requestManager = ClientRequestManager::GetInstance();

		switch (lParam)
		{
		case FD_READ:
			message = requestManager->Recieve(&socket);
			if (!message.empty())
				requestManager->ManageMessage(message);
			break;

		case FD_CLOSE:
			requestManager->GetNetWork()->CloseSocket(socket);
			break;
		default:
			break;
		}

		mClientApp->LeaveMutex();
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
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
}