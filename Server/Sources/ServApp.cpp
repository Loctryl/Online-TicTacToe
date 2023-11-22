#include "Headers/ServerRequestManager.h"
#include "Headers/ServerNetworkMessageWindow.h"
#include "Headers/WebMessageWindow.h"
#include "Headers/NetManager.h"
#include "Headers/ServApp.h"

ServApp::ServApp()
{
	InitializeCriticalSection(&mMutex);// pour creer la critical section

	mMessageWindow = new ServerNetworkMessageWindow(this);
	mMessageWindow->InitWindow(L"NetworkMessageWindow");

	mMessageWebWindow = new WebMessageWindow(this);
	mMessageWebWindow->InitWindow(L"WebMessageWindow");

	mRequestManager = ServerRequestManager::GetInstance();
	mNetManager = new NetManager();
}

ServApp::~ServApp() {
	delete mMessageWindow;
	delete mMessageWebWindow;
	delete mNetManager;
	//delete mRequestManager;
}

bool ServApp::Init()
{
	if (!mRequestManager->Init())
		return false;

	if (!CreateSocketThread())
		return false;

	if (!CreateWebThread())
		return false;

	return true;
}

int ServApp::Run()
{
	if (ResumeThread(mSocketThread) == -1)
	{
		printf("Erreur thread socket\n");
		return 1;
	}

	if (ResumeThread(mWebThread) == -1)
	{
		printf("Erreur thread web\n");
		return 1;
	}

	// Boucle de messages principale :
	do
	{
		Update();
	} while (WaitForSingleObject(mSocketThread, 0) != WAIT_OBJECT_0 && WaitForSingleObject(mWebThread, 0) != WAIT_OBJECT_0);

	DeleteCriticalSection(&mMutex);// quand c'est fini

	CloseHandle(mSocketThread);
	CloseHandle(mWebThread);

	// FERMETURE DU SERVER
	if (!mRequestManager->Close())
		return 1;

	return 0;
}

int ServApp::Update()
{
	return 1;
}

void ServApp::EnterMutex()
{
	EnterCriticalSection(&mMutex);// pour bloquer un bloc d'instructions
}

void ServApp::LeaveMutex()
{
	LeaveCriticalSection(&mMutex);// pour liberer le bloc
}

bool ServApp::CreateSocketThread()
{
	mSocketThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		SocketThreadFunction,	// thread function name
		this,					// argument to thread function 
		CREATE_SUSPENDED,		// Attend l'appel de ResumeThread pour executer le thread
		NULL);					// returns the thread identifier 

	return true;
}

bool ServApp::CreateWebThread()
{
	mWebThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		WebThreadFunction,	// thread function name
		this,					// argument to thread function 
		CREATE_SUSPENDED,		// Attend l'appel de ResumeThread pour executer le thread
		NULL);					// returns the thread identifier 

	return true;
}


DWORD WINAPI ServApp::SocketThreadFunction(LPVOID lpParam)
{
	ServApp* pApp = (ServApp*)lpParam;

	MSG msg = { 0 };

	while (GetMessage(&msg, pApp->mMessageWindow->GetHWND(), 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			break;
	}

	return 0;
}

DWORD WINAPI ServApp::WebThreadFunction(LPVOID lpParam)
{
	ServApp* pApp = (ServApp*)lpParam;

	MSG msg = { 0 };

	while (GetMessage(&msg, pApp->mMessageWebWindow->GetHWND(), 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			break;
	}

	return 0;
}