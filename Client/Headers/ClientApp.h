#pragma once

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
	void Update() const;

	void UpdateInLobby() const;
	void UpdateInGame() const;
	void UpdateGameOver() const;
};