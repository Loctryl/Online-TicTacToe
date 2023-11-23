#include "GameManager.h"
#include "NetWorkThread.h"
#include "Source/ClientApp.h"
#include "..\NetWork\RequestManager.h"

ClientNetWorkThread::ClientNetWorkThread(ClientApp* clientApp) : ThreadObj()
{
	mClientApp = clientApp;
}

ClientNetWorkThread::~ClientNetWorkThread()
{
}

DWORD ClientNetWorkThread::Start()
{
	return ResumeThread(mThread);
}

void ClientNetWorkThread::ThreadFunction()
{
	InitWindow();

	MSG msg = { 0 };

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			break;

		switch (mClientApp->GetGameManager()->mState)
		{
		case LOBBY:
			UpdateInLobby();
			break;
		case IN_GAME:
			UpdateInGame();
			break;
		case GAME_OVER:
			UpdateGameOver();
			break;
		}
	}
}

void ClientNetWorkThread::InitWindow()
{
	mMessageWindow = new ClientNetworkMessageWindow(this);
	mMessageWindow->InitWindow(L"ClientNetworkMessageWindow");
	ClientRequestManager::GetInstance()->Init(this);
}

void ClientNetWorkThread::UpdateInLobby()
{
}

void ClientNetWorkThread::UpdateInGame()
{
}

void ClientNetWorkThread::UpdateGameOver()
{
}
