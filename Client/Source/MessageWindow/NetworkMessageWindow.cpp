#include "GameManager.h"
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

	case WM_JOIN:
	{
		mThread->EnterMutex();
		ClientRequestManager* requestManager = ClientRequestManager::GetInstance();
		requestManager->JoinGame(requestManager->mGame->mInfo[0]);
		mThread->LeaveMutex();
	}
		break;

	case WM_PLAY:
	{
		Choice* choice = (Choice*)wParam;

		mThread->EnterMutex();
		ClientRequestManager* requestManager = ClientRequestManager::GetInstance();
		requestManager->Play(choice->x, choice->y);
		mThread->LeaveMutex();
	}
	break;

	case WM_LEAVE:
	{
		mThread->EnterMutex();
		ClientRequestManager* requestManager = ClientRequestManager::GetInstance();
		requestManager->LeaveGame();
		mThread->LeaveMutex();
	}
	break;
	case WM_USER:
	{
		mThread->EnterMutex();
		ClientRequestManager* requestManager = ClientRequestManager::GetInstance();
		if(requestManager->Init(mThread))
			requestManager->mGame->mConnected = true;
		mThread->LeaveMutex();
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}