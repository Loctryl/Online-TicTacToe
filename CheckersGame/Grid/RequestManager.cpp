#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Headers/RequestManager.h"

RequestManager::RequestManager()
{
}

RequestManager::~RequestManager()
{
}

bool RequestManager::Send(SOCKET socket, const char* sendBuff, size_t bufferSizeData)
{
	if (send(socket, sendBuff, bufferSizeData, 0) == SOCKET_ERROR)
	{
		printf("Erreur send() %d\n", WSAGetLastError());
		return false;
	}
	else
		return true;
}

const char* RequestManager::Recieve(SOCKET socket)
{
	char* recvBuff;
	size_t bufferSizeData = -1;
	int iResult = recv(socket, recvBuff, bufferSizeData, 0);
	if (iResult > 0)
		return recvBuff;
	else
	{
		if (iResult == 0)
			printf("connexion fermee\n");
		else
			printf("Erreur recv() : %d\n", WSAGetLastError());

		return "";
	}
}
