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

	void EnterMutex();
	void LeaveMutex();

private:
	// Thread
	HANDLE mSocketThread;
	HANDLE mWebThread;
	CRITICAL_SECTION mMutex;

	bool CreateSocketThread();
	static DWORD WINAPI SocketThreadFunction(LPVOID lpParam);

	bool CreateWebThread();
	static DWORD WINAPI WebThreadFunction(LPVOID lpParam);
};