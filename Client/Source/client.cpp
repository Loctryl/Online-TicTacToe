#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Ressources/json.hpp"
#include "NetWork.h"
#include "MessageWindow.h"

using json = nlohmann::json;

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	MessageWindow messageWindow = MessageWindow();
	messageWindow.InitWindow();

	NetWork* netWork = NetWork::GetInstance();
	//if (!netWork) return 1;

	int iResult = -1;
	bool endGame = false;
	bool validation = false;
	while (!endGame)
	{
		validation = false;
		while (!validation)
		{
			// ENVOI D'UN DEPLACEMENT
			// récupérer déplacement
			if (!netWork->SendRequest(0, 0))
				return 1;


			// RECEPTION DE LA VALIDATION
			json data = netWork->Recieve();
			
			if (!data)
				return 1;

			validation = data["answer"];
		}

		// faire le d�placement
		// endGame = IsEnd()
		if (endGame)
			break;

		// RECEPTION DU COUP DE L'AUTRE JOUEUR
		json data = netWork->Recieve();
		// faire le d�placement
		// endGame = IsEnd()
	}


	// FERMETURE DU CLIENT
	netWork->Close();
	return 0;
}