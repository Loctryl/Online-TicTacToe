#pragma once
#include "Ressources/framework.h"

class ClientRequestManager;
class MessageWindow;
class GameManager;

class ClientApp
{
	ClientRequestManager* mRequestManager;
	MessageWindow* mMessageWindow;

	GameManager* mGame;
public:
	ClientApp();
	~ClientApp();

	bool Init();

	int Run();
	void Update();

private:
	// Thread
	HANDLE mSocketThread;

	bool CreateSocketThread();
	static DWORD WINAPI SocketThreadFunction(LPVOID lpParam);
};