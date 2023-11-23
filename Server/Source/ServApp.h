#pragma once
#include "Resources/framework.h"

class ServerRequestManager;
class ServerWebRequestManager;
class NetManager;
class ServerNetWorkThread;
class ServerWebThread;
//class GameManager;

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
	int Update();

	void EnterMutex();
	void LeaveMutex();

private:
};