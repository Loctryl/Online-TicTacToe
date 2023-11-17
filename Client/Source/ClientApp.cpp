#include "Headers/ClientApp.h"
//#include "GameManager.h"
#include "Headers/ClientRequestManager.h"


ClientApp::ClientApp() 
{
	mRequestManager = new ClientRequestManager();
	//mGame = new GameManager();
}

ClientApp::~ClientApp() { }

bool ClientApp::Init() 
{
	//mGame->InitGame(5);
	return mRequestManager->Init();
}

int ClientApp::Run() 
{
	bool endGame = false;
	bool validation = false;
	int coord[2] = { -1, -1 };

	int x, y;
	x = -1;
	y = -1;

	/*Event event{};
	while (mGame.IsWindowOpened())
	{
		while (mGame.mWindow->GetWindow()->pollEvent(event))
		{
			if (mGame.IsPressEsc(&event)) mGame.mWindow->GetWindow()->close();
			if (mGame.IsMouseClick(&event) && mGame.IsMove(&x, &y)) {
				mGame.Play(x, y, &Oui);

				x = -1;
				y = -1;
			}
		}
		mGame.RenderGame();
	}*/

	while (!endGame)
	{
		// Premier coup si My Turn == true :
		int Coords[2];
		Coords[0] = -1;
		Coords[1] = -1;
		mRequestManager->SendRequestPlay(Coords);

		std::string Message = "";
		bool validation = false;

		switch (1)// Evenement
		{
		case 1:
			Message = mRequestManager->Recieve();
			validation = mRequestManager->ManageMessage(Message);
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	}


	// FERMETURE DU CLIENT
	if (!mRequestManager->Close())
		return 1;

	return 0;
}