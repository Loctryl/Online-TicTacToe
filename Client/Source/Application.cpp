#include "Headers/Application.h"
#include "Headers/framework.h"


Application::Application() 
{
	mRequestManager = RequestManager();
	mGame = GameManager();
}

Application::~Application() { }

bool Application::Init() 
{
	mGame.InitGame(5);
	return mRequestManager.Init();
}

int Application::Run() 
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
		validation = false;
		while (!validation)
		{
			// ENVOI D'UN DEPLACEMENT
			// récupérer déplacement
			if (!mRequestManager.SendRequest(coord))
				return 1;


			// RECEPTION DE LA VALIDATION
			if (!mRequestManager.RecieveValidation(validation))
				return 1;
		}

		// faire le déplacement
		// endGame = IsEnd()
		if (endGame)
			break;

		// RECEPTION DU COUP DE L'AUTRE JOUEUR
		if (!mRequestManager.RecievePlay(coord))
			return 1;

		// faire le dplacement
		// endGame = IsEnd()
	}


	// FERMETURE DU CLIENT
	if (!mRequestManager.Close())
		return 1;

	return 0;
}