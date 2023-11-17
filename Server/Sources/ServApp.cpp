#include "Headers/ServApp.h"
#include "Headers/ServerRequestManager.h"

ServApp::ServApp()
{
	mRequestManager = new ServerRequestManager();
}

ServApp::~ServApp() { }

bool ServApp::Init()
{
	return mRequestManager->Init();
}

int ServApp::Run()
{
	bool endGame = false;
	bool validation = false;

	std::string Message;

	while (!endGame)
	{
		switch (1)// Evenement
		{
		case 1:// Reception Message
			Message = mRequestManager->Recieve();
			validation = mRequestManager->ManageMessage(Message);
			if (!validation) {
				printf("Error : ManageMessage returned false\n");
			}
			break;

		default:
			break;
		}
	}

	// FERMETURE DU SERVER
	if (!mRequestManager->Close())
		return 1;

	return 0;
}