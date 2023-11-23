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

bool ClientNetWorkThread::Start()
{
	if (ResumeThread(mThread) == -1)
	{
		printf("Erreur thread socket\n");
		return false;
	}

	return true;
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
	}
}

void ClientNetWorkThread::InitWindow()
{
	mMessageWindow = new ClientNetworkMessageWindow(this);
	mMessageWindow->InitWindow(L"ClientNetworkMessageWindow");
}
