#pragma once
#include "framework.h"

class ServerRequestManager;
class ServerNetworkMessageWindow;
class WebMessageWindow;
class NetManager;
//class GameManager;

class ServApp
{
	ServerRequestManager* mRequestManager;
	ServerNetworkMessageWindow* mMessageWindow;
	WebMessageWindow* mMessageWebWindow;
	NetManager* mNetManager;

public:
	ServApp();
	~ServApp();

	bool Init();

	int Run();
	int Update();

	void EnterMutex();
	void LeaveMutex();

private:
	// Thread
	HANDLE mSocketThread;
	HANDLE mWebThread;
	CRITICAL_SECTION mMutex;

	bool CreateSocketThread();
	static DWORD WINAPI SocketThreadFunction(LPVOID lpParam);

	bool CreateWebThread();
	static DWORD WINAPI WebThreadFunction(LPVOID lpParam);
};