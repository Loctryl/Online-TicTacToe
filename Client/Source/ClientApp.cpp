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
	//delete mRequestManager;
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
	while (running && !mRequestManager->GameIsEnded())
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				running = false;
		}

		Update();
		mGame->RenderGame();
	}


	// FERMETURE DU CLIENT
	if (!mRequestManager->Close())
		return 1;

	return 0;
}

void ClientApp::Update()
{
	auto event = mGame->GetEvent();
	while (mGame->mWindow->GetWindow()->pollEvent(*event))
	{
		int x, y = -1;

		if (mGame->IsPressEsc(event)) mGame->mWindow->GetWindow()->close();
		if (mGame->IsMouseClick(event) && mGame->IsMove(&x, &y)) {
			mGame->Play(x, y);
		}
	}
}
