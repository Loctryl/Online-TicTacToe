#include "GameManager.h"
#include "ClientApp.h"
#include "Resources/framework.h"
#include "NetWork\RequestManager.h"
#include "Thread\NetWorkThread.h"

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
		mGame->Render();
		mThread->LeaveMutex();


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
					//mRequestManager->Init(mThread);
					break;
				case 3:
					mThread->EnterMutex();
					mRequestManager->JoinGame();
					mThread->LeaveMutex();
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