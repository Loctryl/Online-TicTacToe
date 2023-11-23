#include "Headers/ClientApp.h"

#include <Grid/Grid.h>

#include "GameManager.h"
#include "Headers/ClientRequestManager.h"
#include "Headers/MessageWindow.h"


ClientApp::ClientApp() 
{
	mMessageWindow = new MessageWindow();
	mMessageWindow->InitWindow();
}

ClientApp::~ClientApp() {
	delete mMessageWindow;
	//delete mRequestManager;
}

bool ClientApp::Init() 
{
	mRequestManager = ClientRequestManager::GetInstance();
	mGame = new GameManager();
	mGame->InitWindow();
	mRequestManager->mGame = mGame;
	return true;
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
		mGame->Render();
	}
	
	// FERMETURE DU CLIENT
	if (!mRequestManager->Close())
		return 1;

	return 0; 
}

void ClientApp::Update() const
{
	switch (mGame->mState)
	{
		case LOBBY:
			UpdateInLobby();
		break;
		case IN_GAME:
			UpdateInGame();
		break;
		case GAME_OVER:
			UpdateGameOver();
		break;
	}
}

void ClientApp::UpdateInLobby() const
{
	auto event = mGame->GetEvent();
	while (mGame->mWindow->GetWindow()->pollEvent(*event))
	{
		if (mGame->IsPressEsc(event)) mGame->mWindow->GetWindow()->close();
		if (mGame->IsMouseClick(event)) {
			int field = mGame->ClickOnField();
			switch (field)
			{
				case 0:
					cout<< "name"<<endl;
					mGame->mSelectedField = 0;
					break;
				case 1:
					cout<< "adress IP"<<endl;
					mGame->mSelectedField = 1;
					break;
				case 2:
					cout << "connect" <<endl;
					mRequestManager->Init();
					break;
				case 3:
					mRequestManager->JoinGame();
					break;
				default: break;
			}
		}
		
		if (event->type == Event::TextEntered)
		{
			if(event->text.unicode == 8 && mGame->mInfo[mGame->mSelectedField].size() > 0)
				mGame->mInfo[mGame->mSelectedField].pop_back();
			else if(event->text.unicode < 128 && mGame->mInfo[mGame->mSelectedField].size() < 12)
				mGame->mInfo[mGame->mSelectedField] += event->text.unicode;
		}
		
	}
}

void ClientApp::UpdateInGame() const
{
	auto event = mGame->GetEvent();
	while (mGame->mWindow->GetWindow()->pollEvent(*event))
	{
		if (mGame->IsPressEsc(event)) mGame->mWindow->GetWindow()->close();
		
		int x, y = -1;

		if (mRequestManager->IsMyTurn() && mGame->IsMouseClick(event) && mGame->IsMove(&x, &y)) {
			int coord[2] = {x, y};
			mRequestManager->Play(coord);
		}
	}
}

void ClientApp::UpdateGameOver() const
{
	auto event = mGame->GetEvent();
	while (mGame->mWindow->GetWindow()->pollEvent(*event))
	{
		if (mGame->IsPressEsc(event)) mGame->mWindow->GetWindow()->close();

		if (mGame->IsMouseClick(event)) {
			mRequestManager->LeaveGame();
		}
	}
}
