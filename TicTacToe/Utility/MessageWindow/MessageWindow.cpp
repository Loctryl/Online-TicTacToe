#include "MessageWindow.h"

MessageWindow::MessageWindow()
{
	hInst = GetModuleHandle(0);
	hPrevInstance = 0;
	lpCmdLine = 0;
	nCmdShow = SW_SHOW;
}

bool MessageWindow::InitWindow(LPCWSTR windowName)
{
	szWindowClass = windowName;
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
		0, 0, 100, 100,
		nullptr, nullptr, hInst, this);
	if (!hWnd)
	{
		cout << "false" << endl;
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

LRESULT CALLBACK MessageWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MessageWindow* messageWindow = nullptr;

	switch (message)
	{
	case WM_CREATE:
	{
		std::cout << "aled2" << endl;

		// Sauvegarde du l'instance de MessageWindow dans la window
		LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
		break;
	}

	default:
	{
		messageWindow = reinterpret_cast<MessageWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		std::cout << messageWindow << endl;
		if(messageWindow)
		{
			return messageWindow->WndInstanceProc(hWnd, message, wParam, lParam);
		}
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
