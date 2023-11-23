#include "NetworkMessageWindow.h"
#include "Source/NetWork/RequestManager.h"
#include "Source/Thread/NetWorkThread.h"
#include "Source/Manager/NetManager.h"

ServerNetworkMessageWindow::ServerNetworkMessageWindow(ServerNetWorkThread* thread) : MessageWindow((ThreadObj*)thread)
{
}

LRESULT ServerNetworkMessageWindow::WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SOCKET socket = wParam;
	SOCKET* newSocket = new SOCKET(INVALID_SOCKET);
	string response = "";

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SOCKET:
	{
		mThread->EnterMutex();
		ServerRequestManager* requestManager = ServerRequestManager::GetInstance();

		switch (LOWORD(lParam))
		{
			case FD_ACCEPT:
				requestManager->GetNetWork()->AcceptClient(newSocket);
				NetManager::GetInstance()->CreatePlayer(newSocket);
				break;

			case FD_READ:
				response = requestManager->Recieve(&socket);
				if (!response.empty())
					requestManager->ManageMessage(response, &socket);
				break;

			case FD_CLOSE:
				requestManager->GetNetWork()->CloseSocket(socket);
				break;
			default:
				break;
		}

		mThread->EnterMutex();
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
