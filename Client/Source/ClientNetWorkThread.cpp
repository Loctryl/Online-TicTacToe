#include "GameManager.h"
#include "Headers/ClientNetWorkThread.h"
#include "Headers/ClientApp.h"
#include "Headers/ClientRequestManager.h"

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
	cout << "inLobby" << endl;
}

void ClientNetWorkThread::UpdateInGame()
{
	cout << "inGame" << endl;
}

void ClientNetWorkThread::UpdateGameOver()
{
	cout << "inGameOver" << endl;
}
