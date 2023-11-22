#pragma once
#include "Headers/framework.h"
#include "Utility/MessageWindow/MessageWindow.h"

class ServApp;

// Handles the Windows window
class WebMessageWindow : public MessageWindow
{
	ServApp* mServerApp;
public:
	WebMessageWindow(ServApp* serverApp);
	~WebMessageWindow() = default;

	LRESULT WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
