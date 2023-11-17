#include "Headers/ServApp.h"
#include "Headers/ServerRequestManager.h"
#include "Headers/MessageWindow.h"

ServApp::ServApp()
{
	mMessageWindow = new MessageWindow();
	mMessageWindow->InitWindow();
	mRequestManager = ServerRequestManager::GetInstance();
}

ServApp::~ServApp() {
	delete mMessageWindow;
	delete mRequestManager;
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

		running = Update();
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
