#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Headers/json.hpp"
#include <Headers/NetWork.h>

using json = nlohmann::json;

#pragma comment(lib, "Ws2_32.lib")

void Close(SOCKET& connectSocket)
{
	int close = closesocket(connectSocket);

	if (close == SOCKET_ERROR)
		printf("Erreur fermeture socket : %d\n", close);
	else
		printf("Socket ferme\n");

	WSACleanup();
}

int main()
{
	NetWork netWork = NetWork();

	if (!netWork.Init())
		return 1;


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
			if (!netWork.SendRequest(0, 0))
				return 1;


			// RECEPTION DE LA VALIDATION
			json data = netWork.Recieve();
			
			if (!data)
				return 1;

			validation = data["answer"];
		}

		// faire le d�placement
		// endGame = IsEnd()
		if (endGame)
			break;

		// RECEPTION DU COUP DE L'AUTRE JOUEUR
		json data = netWork.Recieve();
		// faire le d�placement
		// endGame = IsEnd()
	}


	// FERMETURE DU CLIENT
	netWork.Close();
	return 0;
}