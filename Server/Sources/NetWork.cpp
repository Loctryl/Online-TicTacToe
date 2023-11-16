#pragma comment(lib, "Ws2_32.lib")

#include <cstdio>
#include <WS2tcpip.h>
#include <iostream>

#include "Headers/NetWork.h"

#define PORT 6666
#define ADRESSE "127.0.0.1"
#define PACKET_SIZE 2048


NetWork::NetWork() { }

NetWork::~NetWork() { closesocket(mListenSocket); }

bool NetWork::Init()
{
    if (!SettingSocket())
        return false;

    if (!CreateSocketServer())
        return false;

    sockaddr_in serviceServer = SettingProtocol();

    if (!Bind(serviceServer))
        return false;

    if (!WaitClients())
        return false;

    for (int i = 0; i < NB_CLIENT; i++)
    {
        if (!AcceptClient(i))
        {
            for (int j = 0; j <= i; j++)
                CloseClient(j);

            CloseServer();

            return false;
        }
    }

    return true;
}

bool NetWork::SettingSocket()
{
    WORD wVersionRequested = MAKEWORD(2, 2); // Version min et max de la specification Windows Sockets
    WSADATA wsaData; // Informations sur l implementation de Windows Sockets

    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err)
    {
        printf("Erreur WSAStartup : %d\n", err);
        return false;
    }
    else
        return true;
}

bool NetWork::CreateSocketServer()
{
    mListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mListenSocket == INVALID_SOCKET)
    {
        printf("Erreur Socket : %d\n", WSAGetLastError());
        CloseServer();
        return false;
    }
    else
        return true;
}

sockaddr_in NetWork::SettingProtocol()
{
    sockaddr_in serviceServer;
    serviceServer.sin_family = AF_INET;
    serviceServer.sin_port = htons(PORT);
    inet_pton(AF_INET, ADRESSE, &serviceServer.sin_addr);
    // Convertit une adresse reseau IPv4 ou IPv6 en une forme binaire numerique
    return serviceServer;
}

bool NetWork::Bind(sockaddr_in& serviceServer)
{
    if (bind(mListenSocket, (SOCKADDR*)&serviceServer, sizeof(serviceServer)) == SOCKET_ERROR)// Associe l'adresse locale au socket
    {
        printf("Erreur bind() %d\n", WSAGetLastError());
        CloseServer();
        return false;
    }
    else
        return true;
}

bool NetWork::WaitClients()
{
    if (listen(mListenSocket, NB_CLIENT) == SOCKET_ERROR)
    {
        printf("Erreur lors de l'ecoute : %d\n", WSAGetLastError());
        CloseServer();
        return false;
    }

    printf("Attente de la connexion de 2 clients...\n");
    return true;
}

bool NetWork::AcceptClient(int &numClient)
{
    mAcceptSocket[numClient] = accept(mListenSocket, NULL, NULL);
    if (mAcceptSocket[numClient] == INVALID_SOCKET)
    {
        printf("Erreur accept() socket numero %d : %d\n", numClient, WSAGetLastError());
        return false;
    }
    
    printf("Client connecte\n");
    return true;
}

bool NetWork::SendRequest(const char* data)
{
    if (send(mAcceptSocket[mActualClient], data, PACKET_SIZE, 0) == SOCKET_ERROR)
    {
        printf("Erreur send() %d\n", WSAGetLastError());
        Close();
        return false;
    }

    printf("Requete envoyee\n");
    return true;
}

std::string NetWork::Recieve()
{
    char data[PACKET_SIZE];
    std::string recvString = "";

    int iResult = -1;
    do
    {
        iResult = recv(mAcceptSocket[mActualClient], data, PACKET_SIZE, 0);
        if (iResult > 0)
        {
            data[iResult - 1] = '\0';
            recvString.append(data);
        }
        else if (iResult == 0)
            std::cout << "Recieved Message : " << recvString << "\n";
        else
        {
            printf("Erreur recv() : %d\n", WSAGetLastError());
            Close();
        }

    } while (iResult > 0);

    return recvString;
}

bool NetWork::Close()
{
    bool closeSuccess = true;

    for (int i = 0; i < NB_CLIENT; i++)
    {
        if (!CloseClient(i))
            closeSuccess = false;
    }

    if (!CloseServer())
        closeSuccess = false;

    return closeSuccess;
}

void NetWork::NextClient()
{
    mActualClient = (mActualClient + 1) % 2;
}

bool NetWork::CloseClient(int& numClient)
{
    int close = closesocket(mAcceptSocket[numClient]);

    if (close == SOCKET_ERROR)
    {
        printf("Erreur fermeture socket numero %d : %d\n", numClient, close);
        return false;
    }

    printf("Socket numero %d ferme\n", numClient);
    return true;
}

bool NetWork::CloseServer()
{
    int close = closesocket(mListenSocket);

    WSACleanup();

    if (close == SOCKET_ERROR)
    {
        printf("Erreur fermeture socket serveur\n");
        return false;
    }
    
    printf("Socket serveur ferme\n");
    return true;
}
