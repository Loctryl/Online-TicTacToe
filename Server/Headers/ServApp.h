#pragma once

class ServerRequestManager;
//class GameManager;

class ServApp
{
	ServerRequestManager* mRequestManager;

public:
	ServApp();
	~ServApp();

	bool Init();

	int Run();
};