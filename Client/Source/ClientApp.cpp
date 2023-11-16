#include "Headers/ClientApp.h"
#include "GameManager.h"
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

	// RECEPTION DE LA VALIDATION DE LANCEMENT DE JEU
	if (!mRequestManager->ReceiveValidation(validation))
		return 1;

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
		validation = false;
		while (!validation)
		{
			// ENVOI D'UN DEPLACEMENT
			// recuperer deplacement
			if (!mRequestManager->SendRequest(coord))
				return 1;


			// RECEPTION DE LA VALIDATION DU DEPLACEMENT
			if (!mRequestManager->ReceiveValidation(validation))
				return 1;
		}

		// faire le deplacement
		// endGame = IsEnd()
		if (endGame)
			break;

		// RECEPTION DU COUP DE L'AUTRE JOUEUR
		if (!mRequestManager->RecievePlay(coord))
			return 1;

		// faire le dplacement
		// endGame = IsEnd()
	}


	// FERMETURE DU CLIENT
	if (!mRequestManager->Close())
		return 1;

	return 0;
}