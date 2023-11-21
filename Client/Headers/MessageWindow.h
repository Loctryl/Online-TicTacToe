#pragma once
#include "../Ressources/framework.h"

// Handles the Windows window
class MessageWindow
{
	static HWND hWnd;
	HINSTANCE hInst; // current instance
	WCHAR szWindowClass[100] = L"MessageWindow";

	HINSTANCE hPrevInstance = 0;
	LPWSTR lpCmdLine = 0;
	int nCmdShow = SW_SHOW;

	BOOL InitInstance(CRITICAL_SECTION* mutex);

	ATOM MyRegisterClass();


public:
	MessageWindow();
	~MessageWindow() = default;

	bool InitWindow(CRITICAL_SECTION* mutex);

	static HWND& GetHWND();

	HINSTANCE& GetHInstance();
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);