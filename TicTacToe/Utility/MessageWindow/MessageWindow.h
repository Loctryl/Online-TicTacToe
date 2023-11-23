#pragma once
#include "Utility/Resources/framework.h"

class ThreadObj;

// Handles the Windows window
class MessageWindow
{
	HWND hWnd;
	HINSTANCE hInst; // current instance
	LPCWSTR szWindowClass;

	HINSTANCE hPrevInstance = 0;
	LPWSTR lpCmdLine = 0;
	int nCmdShow = SW_SHOW;

	BOOL InitInstance();

	ATOM MyRegisterClass();

protected:

	ThreadObj* mThread;

public:
	MessageWindow(ThreadObj* mThread);
	virtual ~MessageWindow() = default;

	bool InitWindow(LPCWSTR windowName);

	HWND& GetHWND();

	HINSTANCE& GetHInstance();

	virtual LRESULT WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
