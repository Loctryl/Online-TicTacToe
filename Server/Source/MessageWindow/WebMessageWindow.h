#pragma once
#include "Resources/framework.h"
#include "Utility/MessageWindow/MessageWindow.h"

class ServApp;
class ServerWebThread;

// Handles the Windows window
class WebMessageWindow : public MessageWindow
{
public:
	WebMessageWindow(ServerWebThread* mThread);
	~WebMessageWindow() = default;

	LRESULT WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
