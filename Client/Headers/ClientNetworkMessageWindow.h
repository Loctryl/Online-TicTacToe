#pragma once
#include "../Ressources/framework.h"
#include "Utility/MessageWindow/MessageWindow.h"

class ClientApp;

// Handles the Windows window
class ClientNetworkMessageWindow : public MessageWindow
{
	ClientApp* mClientApp;

public:
	ClientNetworkMessageWindow(ClientApp* clientApp);
	~ClientNetworkMessageWindow() = default;

	LRESULT WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

