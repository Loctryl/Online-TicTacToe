#pragma once
#include "Utility/Thread/Thread.h"
#include "..\MessageWindow\NetworkMessageWindow.h"

class ClientApp;

class ClientNetWorkThread : public ThreadObj
{
	ClientApp* mClientApp;
	ClientNetworkMessageWindow* mMessageWindow;

public:
	ClientNetWorkThread(ClientApp* clientApp);
	~ClientNetWorkThread();

	bool Start();

	void ThreadFunction();

	void InitWindow();

	inline ClientNetworkMessageWindow* GetWindow() { return mMessageWindow; };
};