#include "Headers/WebMessageWindow.h"
#include "Headers/ServerWebRequestManager.h"
#include "Headers/ServerWebThread.h"
#include "Headers/NetManager.h"
#include "Headers/WebManager.h"
#include "Headers/ServApp.h"

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
			mThread->EnterMutex();

			ServerWebRequestManager* requestManager = ServerWebRequestManager::GetInstance();
			requestManager->GetNetWork()->AcceptWebClient(newSocket);
			response = webManager->BuildWebsite();
			if (!requestManager->SendToWeb(response, newSocket))
			{
				mThread->LeaveMutex();
				return 1;
			}
			mThread->LeaveMutex();
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
