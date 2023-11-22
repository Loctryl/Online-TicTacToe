#pragma once
#include "../Ressources/framework.h"
#include "Utility/MessageWindow/MessageWindow.h"

class ClientApp;

// Handles the Windows window
class NetWorkMessageWindow : public MessageWindow
{
	ClientApp* mClientApp;

public:
	NetWorkMessageWindow(ClientApp* clientApp);
	~NetWorkMessageWindow() = default;

	LRESULT WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

