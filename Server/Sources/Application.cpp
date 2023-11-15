#include "Headers/Application.h"
#include "Headers/RequestManager.h"

Application::Application()
{
	mRequestManager = new RequestManager();
}

Application::~Application() { }

bool Application::Init()
{
	return mRequestManager->Init();
}

int Application::Run()
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
		// RECEPTION D'UN DEPLACEMENT
		if (!mRequestManager->RecievePlay(coord))
			return 1;

		// test du deplacement --> validation = true/false
		

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
	}

	// FERMETURE DU SERVER
	if (!mRequestManager->Close())
		return 1;

	return 0;
}