#include "Headers/NetWorkMessageWindow.h"
#include "Headers/ClientRequestManager.h"
#include "Headers/ClientApp.h"

NetWorkMessageWindow::NetWorkMessageWindow(ClientApp* clientApp) : MessageWindow()
{
	mClientApp = clientApp;
}

LRESULT NetWorkMessageWindow::WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SOCKET:
	{
		SOCKET socket = wParam;
		string message = "";

		mClientApp->EnterMutex();

		ClientRequestManager* requestManager = ClientRequestManager::GetInstance();

		switch (lParam)
		{
		case FD_READ:
			message = requestManager->Recieve(&socket);
			if (!message.empty())
				requestManager->ManageMessage(message);
			break;

		case FD_CLOSE:
			requestManager->GetNetWork()->CloseSocket(socket);
			break;
		default:
			break;
		}

		mClientApp->LeaveMutex();
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}