#pragma once
#include "Headers/framework.h"

// Handles the Windows window
class MessageWindow
{
	static HWND hWnd;
	HINSTANCE hInst; // current instance
	WCHAR szWindowClass[100] = L"MessageWindow";

	HINSTANCE hPrevInstance = 0;
	LPWSTR lpCmdLine = 0;
	int nCmdShow = SW_SHOW;

	BOOL InitInstance();

	ATOM MyRegisterClass();


public:
	MessageWindow();
	~MessageWindow() = default;

	bool InitWindow();

	static HWND& GetHWND();

	HINSTANCE& GetHInstance();
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);