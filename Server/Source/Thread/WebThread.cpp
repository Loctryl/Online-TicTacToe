#include "WebThread.h"
#include "Source/NetWork/WebRequestManager.h"

ServerWebThread::ServerWebThread(ServApp* serverApp)
{
	mServerApp = serverApp;
}

ServerWebThread::~ServerWebThread()
{
}

void ServerWebThread::ThreadFunction()
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

void ServerWebThread::InitWindow()
{
	mMessageWindow = new WebMessageWindow(this);
	mMessageWindow->InitWindow(L"ServerNetworkMessageWindow");
	ServerWebRequestManager::GetInstance()->Init(this);
}
