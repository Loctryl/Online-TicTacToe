#pragma comment(lib, "Ws2_32.lib")

#include <cstdio>
#include <WS2tcpip.h>
#include <iostream>

#include "Headers\ServerNetWork.h"

#define PORT 6666
#define ADRESSE "127.0.0.1"
#define PACKET_SIZE 2048
#define SIGNATURE_SIZE 4
#define LENGTH_MESSAGE_SIZE 4
std::uint32_t SIGNATURE = 122943136;



ServerNetWork::ServerNetWork() { }

ServerNetWork::~ServerNetWork() { closesocket(mListenSocket); }

bool ServerNetWork::Init()
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

bool ServerNetWork::SettingSocket()
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

bool ServerNetWork::CreateSocketServer()
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

sockaddr_in ServerNetWork::SettingProtocol()
{
    sockaddr_in serviceServer;
    serviceServer.sin_family = AF_INET;
    serviceServer.sin_port = htons(PORT);
    inet_pton(AF_INET, ADRESSE, &serviceServer.sin_addr);
    // Convertit une adresse reseau IPv4 ou IPv6 en une forme binaire numerique
    return serviceServer;
}

bool ServerNetWork::Bind(sockaddr_in& serviceServer)
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

bool ServerNetWork::WaitClients()
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

bool ServerNetWork::AcceptClient(int &numClient)
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

bool ServerNetWork::SendRequest(std::string data)
{
    SOCKET mConnectSocket = mAcceptSocket[mActualClient];
    int datasize = data.size();
    int total = datasize + SIGNATURE_SIZE + LENGTH_MESSAGE_SIZE;
    char* dataBuffer = new char[total];


    // Making Header
    std::uint32_t sign = SIGNATURE;
    std::uint32_t length = datasize;
    std::memcpy(dataBuffer, &sign, SIGNATURE_SIZE);
    std::memcpy(dataBuffer + SIGNATURE_SIZE, &length, LENGTH_MESSAGE_SIZE);
    std::memcpy(dataBuffer + SIGNATURE_SIZE + LENGTH_MESSAGE_SIZE, data.c_str(), datasize);

    // Sending Message
    if (send(mConnectSocket, dataBuffer, total, 0) == SOCKET_ERROR)
    {
        printf("Erreur send() %d\n", WSAGetLastError());
        Close();
        return false;
    }

    printf("Requete envoyee\n");
    return true;
}

std::string ServerNetWork::Recieve()
{
    SOCKET mConnectSocket = mAcceptSocket[mActualClient];
    char data[PACKET_SIZE];
    std::string recvString = "";

    int iResult = -1;
    iResult = recv(mConnectSocket, data, SIGNATURE_SIZE, 0);
    std::uint32_t MessageSignature;// = new std::uint32_t;
    std::memcpy(&MessageSignature, data, SIGNATURE_SIZE);

    if (MessageSignature != SIGNATURE) {
        printf("Signature non reconnue, message ingore\n");
        return "";
    }

    iResult = recv(mConnectSocket, data, LENGTH_MESSAGE_SIZE, 0);
    std::uint32_t MessageLength; //= new std::uint32_t;
    std::memcpy(&MessageLength, data, LENGTH_MESSAGE_SIZE);


    for (std::uint32_t packet_index = 0; packet_index < MessageLength / PACKET_SIZE; packet_index++) {
        iResult = recv(mConnectSocket, data, PACKET_SIZE, 0);
        recvString.append(data);
    }

    int buffersize = MessageLength % PACKET_SIZE;

    iResult = recv(mConnectSocket, data, buffersize, 0);
    data[iResult] = '\0';
    recvString.append(data);

    printf(recvString.c_str()); printf("\n");

    if (iResult < 0)
    {
        printf("Erreur recv() : %d\n", WSAGetLastError());
        Close();
    }

    return recvString;
}

bool ServerNetWork::Close()
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

void ServerNetWork::NextClient()
{
    mActualClient = (mActualClient + 1) % 2;
}

bool ServerNetWork::CloseClient(int& numClient)
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

bool ServerNetWork::CloseServer()
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
