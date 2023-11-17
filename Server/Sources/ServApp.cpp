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
	int coord[2];

	bool endGame = false;
	bool validation = false;

	// ENVOI DE LA VALIDATION DE LANCEMENT DE JEU
	if (!mRequestManager->SendRequest(validation))
		return 1;
	mRequestManager->NextClient();
	if (!mRequestManager->SendRequest(validation))
		return 1;
	mRequestManager->NextClient();

	while (!endGame)
	{
		switch (1)// Evenement
		{
		case 1:// Reception choix case
			if (!mRequestManager->RecievePlay(coord))
				return 1;

			validation = true;// test le choix et valide/invalide le choix

			// ENVOI DE LA VALIDATION
			if (!mRequestManager->SendRequest(validation))
				return 1;

			if (validation)
			{
				// faire le deplacement
				// MAj endGame
				mRequestManager->NextClient();

				// ENVOI DU DEPLACEMENT A L'AUTRE JOUEUR
				if (!mRequestManager->SendRequest(coord))
					return 1;
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