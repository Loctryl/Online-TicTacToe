#include <cstdio>
#include <WS2tcpip.h>
#include <iostream>

#include "Network.h"

#define PORT 6666
#define ADRESSE "127.0.0.1"
#define PACKET_SIZE 2048
#define SIGNATURE_SIZE 4
#define LENGTH_MESSAGE_SIZE 4
std::uint32_t SIGNATURE = 122943136;



bool Network::Init(SOCKET &sock)
{
    if (!SettingSocket())
        return false;

    if (!CreateSocket(sock))
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

bool Network::CreateSocket(SOCKET &sock)
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
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_port = htons(PORT);
    inet_pton(AF_INET, ADRESSE, &service.sin_addr);
    
    // Convertit une adresse reseau IPv4 ou IPv6 en une forme binaire numerique
    return service;
}

// Sends data from a socket
bool Network::SendRequest(SOCKET &sock, std::string data)
{
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
    if (send(sock, dataBuffer, total, 0) == SOCKET_ERROR)
    {
        printf("Erreur send() %d\n", WSAGetLastError());
        return false;
    }

    printf("Requete envoyee\n");
    return true;
}

bool Network::ErrorRecv(int& iResult)
{
    if (iResult <= 0)
    {
        if (iResult < 0)
            printf("Erreur recv() : %d\n", WSAGetLastError());
        else
            printf("connexion fermee\n");

        return false;
    }
    else
        return true;
}

// Receives information for a given socket
std::string Network::Receive(SOCKET &sock)
{
    char data[PACKET_SIZE];
    std::string recvString = "";

    int iResult = recv(sock, data, SIGNATURE_SIZE, 0);
    if (!ErrorRecv(iResult))
        return "";

    std::uint32_t MessageSignature;// = new std::uint32_t;
    std::memcpy(&MessageSignature, data, SIGNATURE_SIZE);

    if (MessageSignature != SIGNATURE) {
        printf("Signature non reconnue, message ingore\n");
        return "";
    }

    iResult = recv(sock, data, LENGTH_MESSAGE_SIZE, 0);
    if (!ErrorRecv(iResult))
        return "";

    std::uint32_t MessageLength; //= new std::uint32_t;
    std::memcpy(&MessageLength, data, LENGTH_MESSAGE_SIZE);


    for (std::uint32_t packet_index = 0; packet_index < MessageLength / PACKET_SIZE; packet_index++)
    {
        iResult = recv(sock, data, PACKET_SIZE, 0);
        if (!ErrorRecv(iResult))
            return "";

        recvString.append(data);
    }

    int buffersize = MessageLength % PACKET_SIZE;

    iResult = recv(sock, data, buffersize, 0);
    if (!ErrorRecv(iResult))
        return "";

    data[iResult] = '\0';
    recvString.append(data);

    printf("%s\n", recvString.c_str());

    return recvString;
}

bool Network::CloseSocket(SOCKET &sock)
{
    int close = closesocket(sock);

    if (close == SOCKET_ERROR)
    {
        printf("Erreur fermeture socket : %d\n", close);
        return false;
    }

    printf("Socket ferme\n");
    return true;
}