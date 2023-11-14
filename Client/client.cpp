#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

void Close(SOCKET& connectSocket)
{
	int close = closesocket(connectSocket);

	if (close == SOCKET_ERROR)
		printf("Erreur fermeture socket : %d\n", close);
	else
		printf("Socket ferme\n", close);

	WSACleanup();
}


const int nbData = 4;
const size_t bufferSize = sizeof(int) * nbData;

// Sérialisation d'un tableau d'entier
void SerializeIntArray(int array[nbData], char buffer[bufferSize])
{
	memcpy(buffer, array, bufferSize);
}

// Désérialisation d'un tableau d'entier
void DeserializeIntArray(int array[nbData], char buffer[bufferSize])
{
	memcpy(array, buffer, bufferSize);
}

int main()
{
	// TABLEAUX POUR L'ENVOI
	int sendData[nbData];
	char sendBuf[bufferSize];

	// TABLEAUX POUR LA RECEPTION
	int recvData[nbData];
	char recvBuf[bufferSize];


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
	printf("connexion au serveur reussite\n");


	// ENVOI D'UN MESSAGE
	sendData[0] = 1;
	sendData[1] = 12;
	sendData[2] = 4;
	sendData[3] = 0;
	SerializeIntArray(sendData, sendBuf);
	if (send(connectSocket, sendBuf, bufferSize, 0) == SOCKET_ERROR)
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
	do
	{
		iResult = recv(connectSocket, recvBuf, bufferSize, 0);
		if (iResult > 0)
		{
			DeserializeIntArray(recvData, recvBuf);
			printf("Message recu : %d %d %d %d\n", recvData[0], recvData[1], recvData[2], recvData[3]);
		}
		else if (iResult == 0)
			printf("connexion fermee\n");
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