#pragma once

class ServerRequestManager;
class MessageWindow;
class MessageWebWindow;
class NetManager;
//class GameManager;

class ServApp
{
	ServerRequestManager* mRequestManager;
	MessageWindow* mMessageWindow;
	MessageWebWindow* mMessageWebWindow;
	NetManager* mNetManager;

public:
	ServApp();
	~ServApp();

	bool Init();

	int Run();
	int Update();
};