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


//const int nbData = 43;
//const size_t bufferSizeData = sizeof(int) * nbData;
//bool validation = true;
//const size_t bufferSizeValidation = sizeof(bool);
//
//// Sérialisation d'un tableau d'entier
//void SerializeIntArray(int array[nbData], char buffer[bufferSizeData])
//{
//	memcpy(buffer, array, bufferSizeData);
//}
//
//// Désérialisation d'un tableau d'entier
//void DeserializeIntArray(int array[nbData], char buffer[bufferSizeData])
//{
//	memcpy(array, buffer, bufferSizeData);
//}

#define PACKET_SIZE 2048

int main()
{
	// PARAMETRAGE DU SOCKET
	WORD wVersionRequested = MAKEWORD(2, 2);	// Version min et max de la spécification Windows Sockets
	WSADATA wsaData;							// Informations sur l’implémentation de Windows Sockets

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
	inet_pton(AF_INET, "127.0.0.1", &clientService.sin_addr);// Convertit une adresse réseau IPv4 ou IPv6 en une forme binaire numérique


	// CONNEXION AU SERVER
	if (connect(connectSocket, (SOCKADDR*)&clientService, sizeof(clientService)))
	{
		printf("Erreur connect() %d\n", WSAGetLastError());
		Close(connectSocket);
		return 1;
	}
	printf("connexion au serveur reussie\n");


	// ENVOI D'UN MESSAGE

	std::string connectString = R"(
        {
            "connection": "Username"
        }
    )";

	if (send(connectSocket, connectString.c_str(), connectString.size(), 0) == SOCKET_ERROR)
	{
		printf("Erreur send() %d\n", WSAGetLastError());
		Close(connectSocket);
		return 1;
	}
	printf("Message envoye\n");


	// FERMETURE DE LA CONNEXION D'ENVOI (la réception est toujours possible)
	if (shutdown(connectSocket, SD_SEND) == SOCKET_ERROR)
	{
		std::cout << "Erreur shutdown() : " << WSAGetLastError() << "\n";
		Close(connectSocket);
		return 1;
	}
	printf("connexion d'envoi fermee\n");


	// RECEPTION DES MESSAGES
	int iResult = -1;
	char recvBuf[PACKET_SIZE];
	std::string ACKString = "";

	do
	{
		iResult = recv(connectSocket, recvBuf, PACKET_SIZE, 0);
		if (iResult > 0)
		{
			recvBuf[iResult - 1] = '\0';
			ACKString.append(recvBuf);
		}
		else if (iResult == 0)
		{
			std::cout << "Recieved Message : " << ACKString << "\nClosed Connection\n";
		}
		else
		{
			printf("Erreur recv() : %d\n", WSAGetLastError());
			Close(connectSocket);
			return 1;
		}

	} while (iResult > 0);// Tant que la connexion n'est pas fermée ou qu'il n'y a pas eu d'erreurs


	// FERMETURE DU CLIENT
	Close(connectSocket);
	return 0;
}