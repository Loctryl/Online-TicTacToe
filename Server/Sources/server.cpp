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


//const int nbData = 43;
//const size_t bufferSize = sizeof(int) * nbData;
//
//// Sérialisation d'un tableau d'entier
//void SerializeIntArray(int array[nbData], char buffer[bufferSize])
//{
//	memcpy(buffer, array, bufferSize);
//}
//
//// Désérialisation d'un tableau d'entier
//void DeserializeIntArray(int array[nbData], char buffer[bufferSize])
//{
//	memcpy(array, buffer, bufferSize);
//}

#define PACKET_SIZE 2048

int main()
{
	//// TABLEAUX POUR L'ENVOI
	//int sendData[nbData];
	//char sendBuf[bufferSize];

	//// TABLEAUX POUR LA RECEPTION
	//int recvData[nbData];
	//char recvBuf[bufferSize];


	// PARAMETRAGE DU SOCKET
	WORD wVersionRequested = MAKEWORD(2, 2);	// Version min et max de la spécification Windows Sockets
	WSADATA wsaData;							// Informations sur l’implémentation de Windows Sockets

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
	inet_pton(AF_INET, "127.0.0.1", &serviceServer.sin_addr);// Convertit une adresse réseau IPv4 ou IPv6 en une forme binaire numérique

	if (bind(listenSocket, (SOCKADDR*)&serviceServer, sizeof(serviceServer)) == SOCKET_ERROR)// Associe l'adresse locale au socket
	{
		Close(listenSocket);
		WSACleanup();
		return 1;
	}


	// RECHERCHE D'UN CLIENT
	if (listen(listenSocket, 1) == SOCKET_ERROR)
	{
		printf("Erreur lors de l'écoute : %d\n", WSAGetLastError());
		Close(listenSocket);
		WSACleanup();
		return 1;
	}
	printf("Attente de la connexion d'un client...\n");


	// RECUPERATION DU SOCKET CLIENT EN ACCEPTANT LA CONNEXION
	SOCKET acceptSocket = accept(listenSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET)
	{
		printf("Erreur accept() : %d\n", WSAGetLastError());
		Close(listenSocket);
		WSACleanup();
		return 1;
	}
	else
		printf("Client connecte\n");


	// RECEPTION DES MESSAGES

	char recvBuf[PACKET_SIZE];

	int iResult = -1;
	std::string ACKString = "";
	do
	{
		iResult = recv(acceptSocket, recvBuf, PACKET_SIZE, 0);
		if (iResult > 0)
		{
			recvBuf[iResult - 1] = '\0';
			ACKString.append(recvBuf);
		}
		else if (iResult == 0)
			std::cout << "Recieved Message : " << ACKString << "\nClosing Connection\n";
		else
		{
			printf("Erreur recv() : %d\n", WSAGetLastError());
			Close(acceptSocket);
			Close(listenSocket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);// Tant que la connexion n'est pas fermée ou qu'il n'y a pas eu d'erreurs


	// ENVOI D'UN MESSAGE
	//sendData[0] = 2;
	//sendData[1] = 2;
	//sendData[2] = 3;
	//sendData[3] = -1;
	//SerializeIntArray(sendData, sendBuf);

	std::string connectAnswer = R"(
        {
            "start": 1
        }
    )";

	if (send(acceptSocket, connectAnswer.c_str(), connectAnswer.size(), 0) == SOCKET_ERROR)
	{
		printf("Erreur send() %d\n", WSAGetLastError());
		Close(acceptSocket);
		Close(listenSocket);
		WSACleanup();
		return 1;
	}
	printf("Message envoye\n");

	// FERMETURE DE LA CONNEXION
	if (shutdown(acceptSocket, SD_SEND) == SOCKET_ERROR)
	{
		std::cout << "Erreur shutdown() : " << WSAGetLastError() << "\n";
		Close(acceptSocket);
		Close(listenSocket);
		WSACleanup();
		return 1;
	}
	printf("connexion fermee\n");


	// FERMETURE DU SERVER
	Close(acceptSocket);
	Close(listenSocket);
	WSACleanup();
	return 0;
}