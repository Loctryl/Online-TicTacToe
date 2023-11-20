#pragma once
#include "../Ressources/framework.h"

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

private:
	HANDLE mThreadEvent;
	HANDLE mThreadRender;

	bool CreateThreadEvent();
	bool CreateThreadRender();
	static DWORD WINAPI ThreadEventFunction(LPVOID lpParam);
	static DWORD WINAPI ThreadRenderFunction(LPVOID lpParam);
	
	void Update();
};