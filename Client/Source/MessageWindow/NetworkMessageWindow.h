#pragma once
#include "Resources/framework.h"
#include "Utility/MessageWindow/MessageWindow.h"

class ClientNetWorkThread;

// Handles the Windows window
class ClientNetworkMessageWindow : public MessageWindow
{
public:
	ClientNetworkMessageWindow(ClientNetWorkThread* thread);
	~ClientNetworkMessageWindow() = default;

	LRESULT WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

