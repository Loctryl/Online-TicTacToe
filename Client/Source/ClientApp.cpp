#include "GameManager.h"
#include "Headers/ClientRequestManager.h"
#include "Headers/MessageWindow.h"
#include "Headers/ClientApp.h"

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

	if (!CreateThreadEvent())
		return false;

	if (!CreateThreadRender())
		return false;

	return true;
}

int ClientApp::Run() 
{
	printf("Run client\n");

	if (ResumeThread(mThreadEvent) == -1)
	{
		printf("Erreur thread event\n");
		return 1;
	}

	mGame->mWindow->GetWindow()->setActive(false);

	if (ResumeThread(mThreadRender) == -1)
	{
		printf("Erreur thread game\n");
		return 1;
	}

	while (WaitForSingleObject(mThreadEvent, 0) != WAIT_OBJECT_0 && mGame->mWindow->GetWindow()->isOpen())
		Update();

	CloseHandle(mThreadEvent);
	CloseHandle(mThreadRender);


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

		if (mGame->IsPressEsc(event))
			mGame->mWindow->GetWindow()->close();

		if (mRequestManager->IsMyTurn() && mGame->IsMouseClick(event) && mGame->IsMove(&x, &y)) {
			mRequestManager->mMyChoice[0] = x;
			mRequestManager->mMyChoice[1] = y;
			mRequestManager->Play(mRequestManager->mMyChoice);
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
		CREATE_SUSPENDED,		// Attend l'appel de ResumeThread pour exécuter le thread
		NULL);					// returns the thread identifier 

	return true;
}

bool ClientApp::CreateThreadRender()
{
	// Allocation de la mémoire pour pouvoir la gérer
	GameManager* gameManager = (GameManager*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(GameManager));

	if (gameManager == NULL)
		return false;

	gameManager = mGame;

	mThreadRender = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		ThreadRenderFunction,	// thread function name
		gameManager,					// argument to thread function 
		CREATE_SUSPENDED,		// Attend l'appel de ResumeThread pour exécuter le thread
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

DWORD WINAPI ClientApp::ThreadRenderFunction(LPVOID lpParam)
{
	printf("Lancement thread game\n");

	GameManager* gameManager = (GameManager*)lpParam;

	//CRITICAL_SECTION mutex;
	//InitializeCriticalSection(&mutex);// pour créer la critical section
	//EnterCriticalSection(&mutex);// pour bloquer un bloc d'instructions

	//LeaveCriticalSection(&mutex);// pour libérer le bloc
	//DeleteCriticalSection(&mutex);// quand c'est fini

	gameManager->mWindow->GetWindow()->setActive(true);

	while (gameManager->mWindow->GetWindow()->isOpen())
		gameManager->RenderGame();

	printf("Sortie thread game\n");

	return 0;
}

