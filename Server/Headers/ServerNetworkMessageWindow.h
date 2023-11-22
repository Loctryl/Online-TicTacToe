#pragma once
#include "Headers/framework.h"
#include "Utility/MessageWindow/MessageWindow.h"

class ServApp;

// Handles the Windows window
class ServerNetworkMessageWindow : public MessageWindow
{
	ServApp* mServerApp;
public:

	ServerNetworkMessageWindow(ServApp* serverApp);
	~ServerNetworkMessageWindow() = default;

	LRESULT WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
