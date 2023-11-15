#pragma once
#include <windows.h>

// Handles the Windows window
class Window
{
	static HWND hWnd;
	HINSTANCE hInst; // current instance

	HINSTANCE hPrevInstance = 0;
	LPWSTR lpCmdLine = 0;
	int nCmdShow = SW_SHOW;

	BOOL InitInstance();

	ATOM MyRegisterClass();


public:
	Window();
	~Window() = default;

	bool InitWindow();

	static HWND& GetHWND();

	HINSTANCE& GetHInstance();
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);