#include "WebMessageWindow.h"
#include "Source/NetWork/WebRequestManager.h"
#include "Source/Thread/WebThread.h"
#include "Source/Manager/WebManager.h"

WebMessageWindow::WebMessageWindow(ServerWebThread* mThread) : MessageWindow((ThreadObj*)mThread)
{
}

LRESULT WebMessageWindow::WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
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
			ServerWebRequestManager* requestManager = ServerWebRequestManager::GetInstance();
			requestManager->GetNetWork()->AcceptWebClient(newSocket);
			response = webManager->BuildWebsite();
			if (!requestManager->SendToWeb(response, newSocket))
				return 1;
		}
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
