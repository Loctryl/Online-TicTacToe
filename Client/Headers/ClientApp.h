#pragma once
#include "../Ressources/framework.h"

class ClientRequestManager;
class MessageWindow;
class GameManager;

struct DataThreadGame
{
	GameManager* gameManager;
	ClientRequestManager* requestManager;
};

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

private:
	HANDLE mThreadEvent;
	HANDLE mThreadGame;

	bool CreateThreadEvent();
	bool CreateThreadGame();
	static DWORD WINAPI ThreadEventFunction(LPVOID lpParam);
	static DWORD WINAPI ThreadGameFunction(LPVOID lpParam);
	static void Update(GameManager* gameManager, ClientRequestManager* requestManager);
};