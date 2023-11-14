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
		printf("Socket ferme\n");

	WSACleanup();
}


const int nbData = 4;
const size_t bufferSizeData = sizeof(int) * nbData;
bool validation = true;
const size_t bufferSizeValidation = sizeof(bool);

// Sérialisation d'un tableau d'entier
void SerializeIntArray(int array[nbData], char buffer[bufferSizeData])
{
	memcpy(buffer, array, bufferSizeData);
}

// Désérialisation d'un tableau d'entier
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


	int iResult = -1;
	bool endGame = false;
	while (!endGame)
	{
		validation = false;
		while (!validation)
		{
			// ENVOI D'UN DEPLACEMENT
			sendData[0] = 1;
			sendData[1] = 12;
			sendData[2] = 4;
			sendData[3] = 0;
			SerializeIntArray(sendData, sendBuf);
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
				// validation = récup d'un bool
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

		// faire le déplacement
		// MAj endGame
		if (endGame)
			break;

		// RECEPTION DU COUP DE L'AUTRE JOUEUR
		iResult = recv(connectSocket, recvBuf, bufferSizeData, 0);
		if (iResult > 0)
		{
			// réception de son déplacement
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

		// faire le déplacement
		// MAj endGame
	}


	// FERMETURE DU CLIENT
	Close(connectSocket);
	return 0;
}