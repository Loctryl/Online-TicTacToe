#include "NetworkMessageWindow.h"
#include "..\NetWork\RequestManager.h"
#include "..\NetWork\NetWork.h"
#include "..\Thread\NetWorkThread.h"

ClientNetworkMessageWindow::ClientNetworkMessageWindow(ClientNetWorkThread* thread) : MessageWindow((ThreadObj*)thread)
{
}

LRESULT ClientNetworkMessageWindow::WndInstanceProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

		mThread->EnterMutex();

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

		mThread->LeaveMutex();
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}