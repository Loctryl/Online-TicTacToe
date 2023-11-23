#include "Source/ServApp.h"
#include "NetWorkThread.h"
#include "Source/NetWork/RequestManager.h"

ServerNetWorkThread::ServerNetWorkThread(ServApp* serverApp) : ThreadObj()
{
	mServerApp = serverApp;
}

ServerNetWorkThread::~ServerNetWorkThread()
{
}



void ServerNetWorkThread::ThreadFunction()
{
	InitWindow();

	MSG msg = { 0 };

	while (GetMessage(&msg, mMessageWindow->GetHWND(), 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			break;
	}
}

void ServerNetWorkThread::InitWindow()
{
	mMessageWindow = new ServerNetworkMessageWindow(this);
	mMessageWindow->InitWindow(L"ServerNetworkMessageWindow");
	ServerRequestManager::GetInstance()->Init(this);
}