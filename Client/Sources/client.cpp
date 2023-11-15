#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Headers/json.hpp"

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


const int nbData = 4;
const size_t bufferSizeData = sizeof(int) * nbData;
bool validation = true;
const size_t bufferSizeValidation = sizeof(bool);

#define PACKET_SIZE 2048

int main()
{
	// PARAMETRAGE DU SOCKET
	WORD wVersionRequested = MAKEWORD(2, 2);	// Version min et max de la sp�cification Windows Sockets
	WSADATA wsaData;							// Informations sur l�impl�mentation de Windows Sockets

	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err)
	{
		printf("Erreur WSAStartup : %d\n", err);
		return 1;
	}


	// CREATION DU SOCKET CLIENT
	SOCKET connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connectSocket == INVALID_SOCKET)
	{
		printf("Erreur Socket : %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}


	// PARAMETRAGE DU PROTOCOLE
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_port = htons(6666);
	inet_pton(AF_INET, "127.0.0.1", &clientService.sin_addr);// Convertit une adresse r�seau IPv4 ou IPv6 en une forme binaire num�rique


	// CONNEXION AU SERVER
	if (connect(connectSocket, (SOCKADDR*)&clientService, sizeof(clientService)))
	{
		printf("Erreur connect() %d\n", WSAGetLastError());
		Close(connectSocket);
		return 1;
	}
	printf("connexion au serveur reussie\n");


	int iResult = -1;
	bool endGame = false;
	while (!endGame)
	{
		validation = false;
		while (!validation)
		{
			// ENVOI D'UN DEPLACEMENT
			// deplacement(sendData)
			//sendBuf = "{json}";
			if (send(connectSocket, sendBuf, bufferSizeData, 0) == SOCKET_ERROR)
			{
				printf("Erreur send() %d\n", WSAGetLastError());
				Close(connectSocket);
				return 1;
			}
			printf("Message envoye\n");


			// RECEPTION DE LA VALIDATION
			iResult = recv(connectSocket, recvBuf, bufferSizeData, 0);
			if (iResult > 0)
			{
				// validation = r�cup d'un bool
			}
			else
			{
				if (iResult == 0)
					printf("connexion fermee\n");
				else
					printf("Erreur recv() : %d\n", WSAGetLastError());

				Close(connectSocket);
				return 1;
			}
		}

		// faire le d�placement
		// endGame = IsEnd()
		if (endGame)
			break;

		// RECEPTION DU COUP DE L'AUTRE JOUEUR
		iResult = recv(connectSocket, recvBuf, bufferSizeData, 0);
		if (iResult > 0)
		{
			// r�ception de son d�placement
		}
	// // ENVOI D'UN MESSAGE

	// std::string connectString = R"(
    //     {
    //         "connection": "Username"
    //     }
    // )";

	// if (send(connectSocket, connectString.c_str(), connectString.size(), 0) == SOCKET_ERROR)
	// {
	// 	printf("Erreur send() %d\n", WSAGetLastError());
	// 	Close(connectSocket);
	// 	return 1;
	// }
	// printf("Message envoye\n");


	// // FERMETURE DE LA CONNEXION D'ENVOI (la r�ception est toujours possible)
	// if (shutdown(connectSocket, SD_SEND) == SOCKET_ERROR)
	// {
	// 	std::cout << "Erreur shutdown() : " << WSAGetLastError() << "\n";
	// 	Close(connectSocket);
	// 	return 1;
	// }
	// printf("connexion d'envoi fermee\n");


	// // RECEPTION DES MESSAGES
	// int iResult = -1;
	// char recvBuf[PACKET_SIZE];
	// std::string ACKString = "";

	// do
	// {
	// 	iResult = recv(connectSocket, recvBuf, PACKET_SIZE, 0);
	// 	if (iResult > 0)
	// 	{
	// 		recvBuf[iResult - 1] = '\0';
	// 		ACKString.append(recvBuf);
	// 	}
	// 	else if (iResult == 0)
	// 	{
	// 		std::cout << "Recieved Message : " << ACKString << "\nClosed Connection\n";
	// 	}
		else
		{
			if (iResult == 0)
				printf("connexion fermee\n");
			else
				printf("Erreur recv() : %d\n", WSAGetLastError());

			Close(connectSocket);
			return 1;
		}

		// faire le d�placement
		// endGame = IsEnd()
	}


	// FERMETURE DU CLIENT
	Close(connectSocket);
	return 0;
}