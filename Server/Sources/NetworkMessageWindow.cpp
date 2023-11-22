#include "Headers/NetworkMessageWindow.h"
#include "Headers/ServerRequestManager.h"
#include "Headers/NetManager.h"
#include "Headers/WebManager.h"
#include "Headers/ServApp.h"

NetworkMessageWindow::NetworkMessageWindow(ServApp* serverApp) : MessageWindow()
{
	mServerApp = serverApp;
}

LRESULT NetworkMessageWindow::WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	std::cout << "NetworkMessageWindow\n";
	SOCKET socket = wParam;
	SOCKET* newSocket = new SOCKET(INVALID_SOCKET);
	WebManager* webManager = WebManager::GetInstance();
	string response = "";

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SOCKET:
	{
		mServerApp->EnterMutex();
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

		mServerApp->EnterMutex();
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
