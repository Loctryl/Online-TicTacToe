#include "GameManager.h"
#include "Headers/ClientApp.h"
#include "Grid/Grid.h"
#include "Headers/ClientRequestManager.h"
#include "Headers/ClientNetWorkThread.h"

ClientApp::ClientApp() 
{
	mThread = new ClientNetWorkThread(this);
	mRequestManager = ClientRequestManager::GetInstance();
}

ClientApp::~ClientApp() {
	//delete mRequestManager;
}

bool ClientApp::Init() 
{
	mThread->InitThread();
	mRequestManager = ClientRequestManager::GetInstance();
	mGame = new GameManager();
	mGame->InitWindow();
	mRequestManager->mGame = mGame;
	
	return true;
}

int ClientApp::Run() 
{
	if (mThread->Start() == -1)
	{
		printf("Erreur thread socket\n");
		return 1;
	}

	// Boucle de messages principale :
	bool endGame = false;
	do
	{
		Update();

		mThread->EnterMutex();
		endGame = mRequestManager->GameIsEnded();
		mThread->LeaveMutex();

		mGame->Render();

	} while (!endGame);

	
	mThread->CloseThread();

	// FERMETURE DU CLIENT
	if (!mRequestManager->Close())
		return 1;

	return 0; 
}


void ClientApp::Update()
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

void ClientApp::UpdateInLobby()
{
	auto event = mGame->GetEvent();
	while (mGame->mWindow->GetWindow()->pollEvent(*event))
	{
		if (mGame->IsPressEsc(event)) mGame->mWindow->GetWindow()->close();
		if (mGame->IsMouseClick(event))
		{
			mThread->EnterMutex();
			mRequestManager->JoinGame();
			mThread->LeaveMutex();
		}
	}
}

void ClientApp::UpdateInGame()
{
	auto event = mGame->GetEvent();
	while (mGame->mWindow->GetWindow()->pollEvent(*event))
	{
		if (mGame->IsPressEsc(event)) mGame->mWindow->GetWindow()->close();
		
		int x, y = -1;

		if (mGame->IsMouseClick(event) && mGame->IsMove(&x, &y))
		{
			mThread->EnterMutex();

			if (mRequestManager->IsMyTurn())
				mRequestManager->Play(x, y);

			mThread->LeaveMutex();
		}
	}
}

void ClientApp::UpdateGameOver()
{
	auto event = mGame->GetEvent();
	while (mGame->mWindow->GetWindow()->pollEvent(*event))
	{
		if (mGame->IsPressEsc(event)) mGame->mWindow->GetWindow()->close();

		if (mGame->IsMouseClick(event))
		{
			mThread->EnterMutex();

			mRequestManager->LeaveGame();

			mThread->LeaveMutex();
		}
	}
}
