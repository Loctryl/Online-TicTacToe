#pragma once
#include "Utility/Thread/Thread.h"
#include "Headers/ServerNetworkMessageWindow.h"

class ServApp;

class ServerNetWorkThread : public ThreadObj
{
	ServApp* mServerApp;
	ServerNetworkMessageWindow* mMessageWindow;

public:
	ServerNetWorkThread(ServApp* serverApp);
	~ServerNetWorkThread();

	void ThreadFunction();

	void InitWindow();

	inline ServerNetworkMessageWindow* GetWindow() { return mMessageWindow; };
};
