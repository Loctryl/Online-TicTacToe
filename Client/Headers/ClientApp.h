#pragma once

class ClientRequestManager;
//class GameManager;

class ClientApp
{
	ClientRequestManager* mRequestManager;
	//GameManager* mGame;

public:
	ClientApp();
	~ClientApp();

	bool Init();

	int Run();
};