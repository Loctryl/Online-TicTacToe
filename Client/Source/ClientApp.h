#pragma once

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

	inline GameManager* GetGameManager() const { return mGame; }

private:
	void Update() const;

	void UpdateInLobby() const;
	void UpdateInGame() const;
	void UpdateGameOver() const;
};