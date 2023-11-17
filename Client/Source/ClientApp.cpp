#include "Headers/ClientApp.h"
#include "GameManager.h"
#include "Headers/ClientRequestManager.h"
#include "Headers/MessageWindow.h"


ClientApp::ClientApp() 
{
	mMessageWindow = new MessageWindow();
	mMessageWindow->InitWindow();
	mRequestManager = ClientRequestManager::GetInstance();
	mGame = new GameManager();
}

ClientApp::~ClientApp() {
	delete mMessageWindow;
	delete mRequestManager;
}

bool ClientApp::Init() 
{
	mGame->InitWindow();
	return mRequestManager->Init();
}

int ClientApp::Run() 
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
		mGame->RenderGame();
	}


	// FERMETURE DU CLIENT
	if (!mRequestManager->Close())
		return 1;

	return 0;
}

int ClientApp::Update()
{
	return 1;
}
