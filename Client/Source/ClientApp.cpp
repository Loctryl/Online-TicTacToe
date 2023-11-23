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
	if (!mThread->Start())
		return 1;

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
		if (mGame->IsPressEsc(event))
			mGame->mWindow->GetWindow()->close();

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
					break;
				case 3:
					PostMessage(mThread->GetWindow()->GetHWND(), WM_JOIN, 0, 0);
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
		
		Choice* choice = new Choice();
		choice->x = -1;
		choice->y = -1;

		if (mGame->IsMouseClick(event) && mGame->IsMove(&choice->x, &choice->y))
		{
			mThread->EnterMutex();
			bool isMyTurn = mRequestManager->IsMyTurn();
			mThread->LeaveMutex();

			if (isMyTurn)
				PostMessage(mThread->GetWindow()->GetHWND(), WM_PLAY, (WPARAM)choice, 0);

		}
	}
}

void ClientApp::UpdateGameOver()
{
	auto event = mGame->GetEvent();
	while (mGame->mWindow->GetWindow()->pollEvent(*event))
	{
		if (mGame->IsPressEsc(event))
			mGame->mWindow->GetWindow()->close();

		if (mGame->IsMouseClick(event))
			PostMessage(mThread->GetWindow()->GetHWND(), WM_LEAVE, 0, 0);
	}
}