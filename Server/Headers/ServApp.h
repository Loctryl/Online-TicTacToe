#pragma once

class ServerRequestManager;
class NetworkMessageWindow;
class WebMessageWindow;
class NetManager;
//class GameManager;

class ServApp
{
	ServerRequestManager* mRequestManager;
	NetworkMessageWindow* mMessageWindow;
	WebMessageWindow* mMessageWebWindow;
	NetManager* mNetManager;

public:
	ServApp();
	~ServApp();

	bool Init();

	int Run();
	int Update();
};