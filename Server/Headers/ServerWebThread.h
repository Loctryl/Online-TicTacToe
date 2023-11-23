#pragma once
#include "Utility/Thread/Thread.h"
#include "Headers/WebMessageWindow.h"

class ServApp;

class ServerWebThread : public ThreadObj
{
	ServApp* mServerApp;
	WebMessageWindow* mMessageWindow;

public:
	ServerWebThread(ServApp* serverApp);
	~ServerWebThread();

	void ThreadFunction();

	void InitWindow();

	inline WebMessageWindow* GetWindow() { return mMessageWindow; };
};

