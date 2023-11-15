#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Headers/RequestManager.h"

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	RequestManager requestManager = RequestManager();

	if (!requestManager.Init())
		return 1;


	bool endGame = false;
	bool validation = false;
	int coord[2] = { -1, -1 };
	while (!endGame)
	{
		validation = false;
		while (!validation)
		{
			// ENVOI D'UN DEPLACEMENT
			// récupérer déplacement
			if (!requestManager.SendRequest(coord))
				return 1;


			// RECEPTION DE LA VALIDATION
			if (!requestManager.RecieveValidation(validation))
				return 1;
		}

		// faire le déplacement
		// endGame = IsEnd()
		if (endGame)
			break;

		// RECEPTION DU COUP DE L'AUTRE JOUEUR
		if (!requestManager.RecievePlay(coord))
			return 1;

		// faire le d�placement
		// endGame = IsEnd()
	}


	// FERMETURE DU CLIENT
	if (!requestManager.Close())
		return 1;

	return 0;
}