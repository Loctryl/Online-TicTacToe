#pragma once
#include "Resources/framework.h"

class ServerRequestManager;
class ServerWebRequestManager;
class NetManager;
class ServerNetWorkThread;
class ServerWebThread;

class ServApp
{
	ServerRequestManager* mRequestManager;
	ServerWebRequestManager* mWebRequestManager;
	ServerNetWorkThread* mNetWorkThread;
	ServerWebThread* mWebThread;
	NetManager* mNetManager;

public:
	ServApp();
	~ServApp();

	bool Init();

	int Run();

	void EnterMutex();
	void LeaveMutex();

private:
};