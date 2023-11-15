#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Headers/json.hpp"
using json = nlohmann::json;

#pragma comment(lib, "Ws2_32.lib")

void Close(SOCKET& socket)
{
	int close = closesocket(socket);

	if (close == SOCKET_ERROR)
		printf("Erreur fermeture socket : %d\n", close);
	else
		printf("Socket ferme\n");
}


const int nbData = 4;
const size_t bufferSizeData = sizeof(int) * nbData;
bool validation = true;
const size_t bufferSizeValidation = sizeof(bool);

// S�rialisation d'un tableau d'entier
void SerializeIntArray(int array[nbData], char buffer[bufferSizeData])
{
	memcpy(buffer, array, bufferSizeData);
}

// D�s�rialisation d'un tableau d'entier
void DeserializeIntArray(int array[nbData], char buffer[bufferSizeData])
{
	memcpy(array, buffer, bufferSizeData);
}

int main()
{
	// TABLEAUX POUR L'ENVOI
	int sendData[nbData];
	char sendBuf[bufferSizeData];

	// TABLEAUX POUR LA RECEPTION
	int recvData[nbData];
	char recvBuf[bufferSizeData];


	// PARAMETRAGE DU SOCKET
	WORD wVersionRequested = MAKEWORD(2, 2);	// Version min et max de la sp�cification Windows Sockets
	WSADATA wsaData;							// Informations sur l�impl�mentation de Windows Sockets

	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err)
	{
		printf("Erreur WSAStartup : %d\n", err);
		return 1;
	}


	// CREATION DU SOCKET SERVER
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("Erreur Socket : %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}


	// PARAMETRAGE DU PROTOCOLE
	sockaddr_in serviceServer;
	serviceServer.sin_family = AF_INET;
	serviceServer.sin_port = htons(6666);
	inet_pton(AF_INET, "127.0.0.1", &serviceServer.sin_addr);// Convertit une adresse r�seau IPv4 ou IPv6 en une forme binaire num�rique

	if (bind(listenSocket, (SOCKADDR*)&serviceServer, sizeof(serviceServer)) == SOCKET_ERROR)// Associe l'adresse locale au socket
	{
		Close(listenSocket);
		WSACleanup();
		return 1;
	}


	// RECHERCHE DE 2 CLIENTs
	if (listen(listenSocket, 2) == SOCKET_ERROR)
	{
		printf("Erreur lors de l'�coute : %d\n", WSAGetLastError());
		Close(listenSocket);
		WSACleanup();
		return 1;
	}
	printf("Attente de la connexion de 2 clients...\n");


	// RECUPERATION DU SOCKET CLIENT EN ACCEPTANT LA CONNEXION
	SOCKET acceptSocket1 = accept(listenSocket, NULL, NULL);
	if (acceptSocket1 == INVALID_SOCKET)
	{
		printf("Erreur accept() : %d\n", WSAGetLastError());
		Close(listenSocket);
		WSACleanup();
		return 1;
	}
	else
		printf("Client connecte\n");

	// RECUPERATION DU SOCKET CLIENT EN ACCEPTANT LA CONNEXION
	SOCKET acceptSocket2 = accept(listenSocket, NULL, NULL);
	if (acceptSocket2 == INVALID_SOCKET)
	{
		printf("Erreur accept() : %d\n", WSAGetLastError());
		Close(acceptSocket1);
		Close(listenSocket);
		WSACleanup();
		return 1;
	}
	else
		printf("Client connecte\n");

	// STOCKAGE DES 2 CLIENTS
	SOCKET acceptSocket[2] = { acceptSocket1, acceptSocket2 };
	int clientActu = 0;


	int iResult = -1;
	bool endGame = false;
	do
	{
		// RECEPTION  D'UN DEPLACEMENT
		iResult = recv(acceptSocket[clientActu], recvBuf, bufferSizeData, 0);
		if (iResult > 0)
		{
			// reception deplacement
			// test du deplacement
			// validation = true/false
		}
		else
		{
			if (iResult == 0)
				printf("connexion fermee\n");
			else
				printf("Erreur recv() : %d\n", WSAGetLastError());

			Close(acceptSocket[0]);
			Close(acceptSocket[1]);
			Close(listenSocket);
			WSACleanup();
			return 1;
		}

		// ENVOI DE LA VALIDATION
		if (send(acceptSocket[clientActu], sendBuf, bufferSizeData, 0) == SOCKET_ERROR)
		{
			printf("Erreur send() %d\n", WSAGetLastError());
			Close(acceptSocket[0]);
			Close(acceptSocket[1]);
			Close(listenSocket);
			WSACleanup();
			return 1;
		}
		printf("Message envoye\n");

		if (validation)
		{
			// faire le d�placement
			// MAj endGame
			// changer le acceptSocket
			// envoie du d�plcement � l'autre joueur
		}


	} while (false);// Tant que la connexion n'est pas ferm�e ou qu'il n'y a pas eu d'erreurs


	// FERMETURE DE LA CONNEXION
	if (shutdown(acceptSocket[0], SD_BOTH) == SOCKET_ERROR)
	{
		std::cout << "Erreur shutdown() : " << WSAGetLastError() << "\n";
		Close(acceptSocket[0]);
		Close(acceptSocket[1]);
		Close(listenSocket);
		WSACleanup();
		return 1;
	}
	printf("connexion fermee\n");

	// FERMETURE DE LA CONNEXION
	if (shutdown(acceptSocket[1], SD_BOTH) == SOCKET_ERROR)
	{
		std::cout << "Erreur shutdown() : " << WSAGetLastError() << "\n";
		Close(acceptSocket[0]);
		Close(acceptSocket[1]);
		Close(listenSocket);
		WSACleanup();
		return 1;
	}
	printf("connexion fermee\n");


	// FERMETURE DU SERVER
	Close(acceptSocket[0]);
	Close(acceptSocket[1]);
	Close(listenSocket);
	WSACleanup();
	return 0;
}