#include "Headers/ServApp.h"
#include "Headers/ServerRequestManager.h"
#include "Headers/ServerWebRequestManager.h"
#include "Headers/ServerNetWorkThread.h"
#include "Headers/ServerWebThread.h"
#include "Headers/NetManager.h"

ServApp::ServApp()
{
	mNetWorkThread = new ServerNetWorkThread(this);
	mWebThread = new ServerWebThread(this);

	mRequestManager = ServerRequestManager::GetInstance();
	mWebRequestManager = ServerWebRequestManager::GetInstance();
	mNetManager = new NetManager();
}

ServApp::~ServApp() {
	delete mNetManager;
	//delete mRequestManager;
}

bool ServApp::Init()
{
	if (!mNetWorkThread->InitThread())
		return false;

	if (!mWebThread->InitThread())
		return false;

	return true;
}

int ServApp::Run()
{
	if (mNetWorkThread->Start() == -1)
	{
		printf("Erreur thread socket\n");
		return 1;
	}

	if (mWebThread->Start() == -1)
	{
		printf("Erreur thread web\n");
		return 1;
	}

	// Boucle de messages principale :
	do
	{
		Update();
	} while (WaitForSingleObject(mNetWorkThread, 0) != WAIT_OBJECT_0 && WaitForSingleObject(mWebThread, 0) != WAIT_OBJECT_0);

	mNetWorkThread->CloseThread();
	mWebThread->CloseThread();

	// FERMETURE DU SERVER
	if (!mRequestManager->Close())
		return 1;

	return 0;
}

int ServApp::Update()
{
	return 1;
}