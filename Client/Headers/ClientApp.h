#pragma once
#include "Ressources/framework.h"

class ClientRequestManager;
class ClientNetworkMessageWindow;
class GameManager;

class ClientApp
{
	ClientRequestManager* mRequestManager;
	ClientNetworkMessageWindow* mMessageWindow;

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

	void UpdateInLobby();
	void UpdateInGame();
	void UpdateGameOver();
};