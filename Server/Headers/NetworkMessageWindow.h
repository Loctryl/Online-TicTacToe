#pragma once
#include "Headers/framework.h"
#include "Utility/MessageWindow/MessageWindow.h"

class ServApp;

// Handles the Windows window
class NetworkMessageWindow : public MessageWindow
{
	ServApp* mServerApp;
public:

	NetworkMessageWindow(ServApp* serverApp);
	~NetworkMessageWindow() = default;

	LRESULT WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
