#pragma comment(lib, "Ws2_32.lib")

#include <cstdio>
#include <WS2tcpip.h>
#include <iostream>

#include "NetWork.h"

#define PORT 6666
#define ADRESSE "127.0.0.1"
#define PACKET_SIZE 2048

// Takes a socket to init as a client to send and receive data from a server
bool Network::InitAsClient(SOCKET sock)
{
    if (!SettingSocket())
        return false;

    if (!CreateSocket(sock))
        return false;

    sockaddr_in clientService = SettingProtocol();

    if (!ConnectServer(sock, clientService))
        return false;

    return true;
}

// Takes a socket to init as a server to send and receive data from clients
bool Network::InitAsServer(SOCKET sock)
{
    if (!SettingSocket())
        return false;

    if (!CreateSocket(sock))
        return false;

    sockaddr_in serviceServer = SettingProtocol();

    if (!Bind(sock, serviceServer))
        return false;

    if (!WaitClients(sock))
        return false;

    return true;
}

bool Network::SettingSocket()
{
    constexpr WORD wVersionRequested = MAKEWORD(2, 2); // Version min et max de la specification Windows Sockets
    WSADATA wsaData; // Information sur l implementation de Windows Sockets

    if (const int err = WSAStartup(wVersionRequested, &wsaData))
    {
        printf("Erreur WSAStartup : %d\n", err);
        return false;
    }
    return true;
}

bool Network::CreateSocket(SOCKET sock)
{
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        printf("Erreur Socket : %d\n", WSAGetLastError());
        WSACleanup();
        return false;
    }
    return true;
}

sockaddr_in Network::SettingProtocol()
{
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_port = htons(PORT);
    inet_pton(AF_INET, ADRESSE, &clientService.sin_addr);
    
    // Convertit une adresse reseau IPv4 ou IPv6 en une forme binaire numerique
    return clientService;
}

// Connects a given socket to a server address
bool Network::ConnectServer(SOCKET sock, sockaddr_in& clientService)
{
    if (connect(sock, (SOCKADDR*)&clientService, sizeof(clientService)))
    {
        printf("Erreur connect() %d\n", WSAGetLastError());
        CloseSocket(sock);
        return false;
    }

    printf("connexion au serveur reussite\n");
    return true;
}

// Takes a socket server to bind it to the address
bool Network::Bind(SOCKET sock, sockaddr_in& serviceServer)
{
    if (bind(sock, (SOCKADDR*)&serviceServer, sizeof(serviceServer)) == SOCKET_ERROR)// Associe l'adresse locale au socket
        {
        printf("Erreur bind() %d\n", WSAGetLastError());
        CloseSocket(sock);
        return false;
        }
    else
        return true;
}

// Binds the given server socket to listen to clients
bool Network::WaitClients(SOCKET sock)
{
    if (listen(sock, NB_CLIENT) == SOCKET_ERROR)
    {
        printf("Erreur lors de l'ecoute : %d\n", WSAGetLastError());
        CloseSocket(sock);
        return false;
    }

    printf("Attente de la connexion de 2 clients...\n");
    return true;
}

// Link a given client socket to a given server socket
bool Network::AcceptClient(SOCKET sockClient, SOCKET sockServer)
{
    sockClient = accept(sockServer, NULL, NULL);
    if (sockClient == INVALID_SOCKET)
    {
        printf("Erreur accept() socket numero : %d\n", WSAGetLastError());
        return false;
    }
    
    printf("Client connecte\n");
    return true;
}

// Sends data from a socket
bool Network::SendRequest(SOCKET sock, const char* data)
{
    if (send(sock, data, PACKET_SIZE, 0)==SOCKET_ERROR)
    {
        printf("Erreur send() %d\n", WSAGetLastError());
        CloseSocket(sock);
        return false;
    }

    printf("Requete envoyee\n");
    return true;
}

// Receives information for a given socket
std::string Network::Receive(SOCKET sock)
{
    char data[PACKET_SIZE];
    std::string recvString = "";

    int iResult = -1;
    do
    {
        iResult = recv(sock, data, PACKET_SIZE, 0);
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
            CloseSocket(sock);
        }

    } while (iResult > 0);

    return recvString;
}

bool Network::CloseSocket(SOCKET sock)
{
    const int close = closesocket(sock);
    WSACleanup();

    if (close==SOCKET_ERROR)
    {
        printf("Erreur fermeture socket : %d\n", close);
        return false;
    }
    else
    {
        printf("Socket ferme\n");
        return true;
    }
}