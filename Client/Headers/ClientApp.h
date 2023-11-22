#pragma once
#include "Ressources/framework.h"

class ClientRequestManager;
class NetWorkMessageWindow;
class GameManager;

class ClientApp
{
	ClientRequestManager* mRequestManager;
	NetWorkMessageWindow* mMessageWindow;

	GameManager* mGame;
public:
	ClientApp();
	~ClientApp();

	bool Init();

	int Run();

	void EnterMutex();
	void LeaveMutex();

private:
	void Update();

	// Thread
	HANDLE mSocketThread;
	CRITICAL_SECTION mMutex;

	bool CreateSocketThread();
	static DWORD WINAPI SocketThreadFunction(LPVOID lpParam);
};