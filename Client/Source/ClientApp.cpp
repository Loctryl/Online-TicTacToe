
#include "GameManager.h"
#include "Headers/ClientRequestManager.h"
#include "Headers/MessageWindow.h"
#include "Headers/ClientApp.h"

ClientApp::ClientApp() 
{
	mRequestManager = ClientRequestManager::GetInstance();
	mGame = new GameManager(mRequestManager->mGrid);
}

ClientApp::~ClientApp() {
	delete mMessageWindow;
	//delete mRequestManager;
}

bool ClientApp::Init() 
{
	mGame->InitWindow();

	if (!CreateSocketThread())
		return false;
	else
		return true;
}

int ClientApp::Run() 
{
	if (ResumeThread(mSocketThread) == -1)
	{
		printf("Erreur thread socket\n");
		return 1;
	}

	// Boucle de messages principale :
	while (/*WaitForSingleObject(mSocketThread, 0) != WAIT_OBJECT_0 &&*/ !mRequestManager->GameIsEnded())
	{
		Update();
		mGame->RenderGame();
	}

	CloseHandle(mSocketThread);

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
		if (mRequestManager->IsMyTurn() && mGame->IsMouseClick(event) && mGame->IsMove(&x, &y)) {
			mRequestManager->mMyChoice[0] = x;
			mRequestManager->mMyChoice[1] = y;
			mRequestManager->Play(mRequestManager->mMyChoice);
		}
	}
}

bool ClientApp::CreateSocketThread()
{
	mSocketThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		SocketThreadFunction,	// thread function name
		this,					// argument to thread function 
		CREATE_SUSPENDED,		// Attend l'appel de ResumeThread pour exécuter le thread
		NULL);					// returns the thread identifier 

	return true;
}

DWORD WINAPI ClientApp::SocketThreadFunction(LPVOID lpParam)
{
	ClientApp* pApp = (ClientApp*)lpParam;

	pApp->mMessageWindow = new MessageWindow();
	pApp->mMessageWindow->InitWindow();

	pApp->mRequestManager->Init();

	MSG msg = { 0 };

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			break;
	}

	return 0;
}

