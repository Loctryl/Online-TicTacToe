#pragma once
#include "../Ressources/framework.h"

class ClientApp;

// Handles the Windows window
class MessageWindow
{
	ClientApp* mClientApp;

	static HWND hWnd;
	HINSTANCE hInst; // current instance
	WCHAR szWindowClass[100] = L"MessageWindow";

	HINSTANCE hPrevInstance = 0;
	LPWSTR lpCmdLine = 0;
	int nCmdShow = SW_SHOW;

	BOOL InitInstance();

	ATOM MyRegisterClass();


public:
	MessageWindow(ClientApp* clientApp);
	~MessageWindow() = default;

	bool InitWindow();

	static HWND& GetHWND();

	HINSTANCE& GetHInstance();

	LRESULT WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

