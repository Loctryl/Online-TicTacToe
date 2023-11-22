#include "Headers/WebMessageWindow.h"
#include "Headers/ServerRequestManager.h"
#include "Headers/NetManager.h"
#include "Headers/WebManager.h"

WebMessageWindow::WebMessageWindow(ServApp* serverApp) : MessageWindow()
{
	mServerApp = serverApp;
}

LRESULT WebMessageWindow::WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	SOCKET socket = wParam;
	SOCKET* newSocket = new SOCKET(INVALID_SOCKET);
	ServerRequestManager* requestManager = ServerRequestManager::GetInstance();// TO DO : A remplacer par RequestManager*, non ?
	WebManager* webManager = WebManager::GetInstance();
	string response = "";

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_WEBSOCKET:
	{
		switch (LOWORD(lParam))
		{
		case FD_ACCEPT:
			requestManager->GetNetWork()->AcceptWebClient(newSocket);
			response = webManager->BuildWebsite();
			if (!requestManager->SendToWeb(response, newSocket))
				return 1;
			//requestManager->GetNetWork()->CloseSocket(newSocket);
			break;
		default:
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
