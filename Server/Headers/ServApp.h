#pragma once

class ServerRequestManager;
class MessageWindow;
//class GameManager;

class ServApp
{
	ServerRequestManager* mRequestManager;
	MessageWindow* mMessageWindow;
public:
	ServApp();
	~ServApp();

	bool Init();

	int Run();
	int Update();
};