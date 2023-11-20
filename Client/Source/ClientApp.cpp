#include "GameManager.h"
#include "Headers/ClientRequestManager.h"
#include "Headers/MessageWindow.h"
#include "Headers/ClientApp.h"

HANDLE ClientApp::mutex = CreateMutex(
	NULL,              // default security attributes
	FALSE,             // initially not owned
	NULL);             // unnamed mutex


ClientApp::ClientApp() 
{
	mMessageWindow = new MessageWindow();
	mMessageWindow->InitWindow();
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
	if (!mRequestManager->Init())
		return false;

	//if (!CreateThreadEvent())
		//return false;

	if (mutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return false;
	}

	if (!CreateThreadGame())
		return false;

	return true;
}

int ClientApp::Run() 
{
	printf("Run client\n");

	/*if (ResumeThread(mThreadEvent) == -1)
	{
		printf("Erreur thread event\n");
		return 1;
	}*/

	if (ResumeThread(mThreadGame) == -1)
	{
		printf("Erreur thread game\n");
		return 1;
	}

	while (/*WaitForSingleObject(mThreadEvent, INFINITE) != WAIT_OBJECT_0 &&*/ WaitForSingleObject(mThreadGame, INFINITE) != WAIT_OBJECT_0)
		continue;

	// FERMETURE DU CLIENT
	if (!mRequestManager->Close())
		return 1;

	return 0;
}



void ClientApp::Update(GameManager* gameManager, ClientRequestManager* requestManager)
{
	auto event = gameManager->GetEvent();
	while (gameManager->mWindow->GetWindow()->pollEvent(*event))
	{
		int x, y = -1;

		if (gameManager->IsPressEsc(event)) gameManager->mWindow->GetWindow()->close();
		if (requestManager->IsMyTurn() && gameManager->IsMouseClick(event) && gameManager->IsMove(&x, &y)) {
			requestManager->mMyChoice[0] = x;
			requestManager->mMyChoice[1] = y;
			requestManager->Play(requestManager->mMyChoice);
		}
	}
}

bool ClientApp::CreateThreadEvent()
{
	mThreadEvent = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		ThreadEventFunction,	// thread function name
		NULL,					// argument to thread function 
		CREATE_SUSPENDED,		// Attend l'appel de ResumeThread pour ex�cuter le thread
		NULL);					// returns the thread identifier 

	return true;
}

bool ClientApp::CreateThreadGame()
{
	// Allocation de la m�moire pour pouvoir la g�rer
	DataThreadGame* dtg = (DataThreadGame*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(DataThreadGame));

	if (dtg == NULL)
		return false;

	dtg->gameManager = mGame;
	dtg->requestManager = mRequestManager;

	mThreadGame = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		ThreadGameFunction,	// thread function name
		dtg,					// argument to thread function 
		CREATE_SUSPENDED,		// Attend l'appel de ResumeThread pour ex�cuter le thread
		NULL);					// returns the thread identifier 

	return true;
}

DWORD WINAPI ClientApp::ThreadEventFunction(LPVOID lpParam)
{
	printf("Lancement thread event\n");

	bool running = true;
	MSG msg = { 0 };

	while (running)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				running = false;
		}
	}

	printf("Sortie thread event\n");

	return 0;
}

DWORD WINAPI ClientApp::ThreadGameFunction(LPVOID lpParam)
{
	printf("Lancement thread game\n");

	DataThreadGame* dtg = (DataThreadGame*)lpParam;

	DWORD waitResult = WaitForSingleObject(
		mutex,    // handle to mutex
		INFINITE);  // no time-out interval

	printf("Test 1\n");

	while (!dtg->requestManager->GameIsEnded())
	{
		Update(dtg->gameManager, dtg->requestManager);
		dtg->gameManager->RenderGame();
	}

	printf("Test 2\n");

	if (!ReleaseMutex(mutex))
	{
		printf("Erreur lib�ration mutex");
	}

	CloseHandle(mutex);

	printf("Sortie thread game\n");

	return 0;
}

