#include "Headers/WebMessageWindow.h"
#include "Headers/ServerRequestManager.h"
#include "Headers/NetManager.h"
#include "Headers/WebManager.h"
#include "Headers/ServApp.h"

WebMessageWindow::WebMessageWindow(ServApp* serverApp) : MessageWindow()
{
	mServerApp = serverApp;
}

LRESULT WebMessageWindow::WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	std::cout << "WebMessageWindow\n";
	SOCKET socket = wParam;
	SOCKET* newSocket = new SOCKET(INVALID_SOCKET);
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
		{
			mServerApp->EnterMutex();

			ServerRequestManager* requestManager = ServerRequestManager::GetInstance();
			requestManager->GetNetWork()->AcceptWebClient(newSocket);
			response = webManager->BuildWebsite();
			if (!requestManager->SendToWeb(response, newSocket))
			{
				mServerApp->LeaveMutex();
				return 1;
			}
			mServerApp->LeaveMutex();
		}
			

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
