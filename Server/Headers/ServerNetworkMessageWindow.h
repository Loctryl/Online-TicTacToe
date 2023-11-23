#pragma once
#include "Headers/framework.h"
#include "Utility/MessageWindow/MessageWindow.h"

class ServerNetWorkThread;

// Handles the Windows window
class ServerNetworkMessageWindow : public MessageWindow
{
public:
	ServerNetworkMessageWindow(ServerNetWorkThread* thread);
	~ServerNetworkMessageWindow() = default;

	LRESULT WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
