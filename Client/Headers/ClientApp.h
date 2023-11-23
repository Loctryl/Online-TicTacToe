#pragma once
#include "Ressources/framework.h"

class ClientRequestManager;
class ClientNetWorkThread;
class GameManager;

class ClientApp
{
	ClientRequestManager* mRequestManager;
	ClientNetWorkThread* mThread;

	GameManager* mGame;

public:
	ClientApp();
	~ClientApp();

	bool Init();

	int Run();

	inline GameManager* GetGameManager() { return mGame; };

private:
	void Update();

	void UpdateInLobby();
	void UpdateInGame();
	void UpdateGameOver();
};