#pragma once

class ServerRequestManager;
class MessageWindow;
class NetManager;
//class GameManager;

class ServApp
{
	ServerRequestManager* mRequestManager;
	MessageWindow* mMessageWindow;
	NetManager* mNetManager;

public:
	ServApp();
	~ServApp();

	bool Init();

	int Run();
	int Update();
};