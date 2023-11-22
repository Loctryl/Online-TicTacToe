#include "Headers/ServerRequestManager.h"
#include "Headers/NetWorkMessageWindow.h"
#include "Headers/WebMessageWindow.h"
#include "Headers/NetManager.h"
#include "Headers/ServApp.h"

ServApp::ServApp()
{
	mMessageWindow = new NetworkMessageWindow(this);
	mMessageWindow->InitWindow();
	mMessageWebWindow = new WebMessageWindow(this);
	mMessageWebWindow->InitWindow();
	mRequestManager = ServerRequestManager::GetInstance();
	mNetManager = new NetManager();
}

ServApp::~ServApp() {
	delete mMessageWindow;
	delete mMessageWebWindow;
	delete mNetManager;
	//delete mRequestManager;
}

bool ServApp::Init()
{
	return mRequestManager->Init();
}

int ServApp::Run()
{

	MSG msg = { 0 };

	bool running = true;

	// Boucle de messages principale :
	while (running)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				running = false;
		}

		Update();
	}

	return (int)msg.wParam;

	// FERMETURE DU SERVER
	if (!mRequestManager->Close())
		return 1;

	return 0;
}

int ServApp::Update()
{
	return 1;
}