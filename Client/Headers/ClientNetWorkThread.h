#pragma once
#include "Utility/Thread/Thread.h"
#include "Headers/ClientNetworkMessageWindow.h"

class ClientApp;

class ClientNetWorkThread : public ThreadObj
{
	ClientApp* mClientApp;
	ClientNetworkMessageWindow* mMessageWindow;

public:
	ClientNetWorkThread(ClientApp* clientApp);
	~ClientNetWorkThread();

	DWORD Start();

	void ThreadFunction();

	void InitWindow();
	void UpdateInLobby();
	void UpdateInGame();
	void UpdateGameOver();

	inline ClientNetworkMessageWindow* GetWindow() { return mMessageWindow; };
};