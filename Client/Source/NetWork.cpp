#include "NetWork.h"

NetWork::NetWork()
{
}

NetWork::~NetWork()
{
    closesocket(mConnectSocket);
}

bool NetWork::Init()
{
    if (!SettingSocket())
        return false;

    if (!CreateSocket())
        return false;

    sockaddr_in clientService = SettingProtocol();
    
    if (!ConnectServer(clientService))
        return false;

    return true;
}

bool NetWork::SettingSocket()
{
    WORD wVersionRequested = MAKEWORD(2, 2);	// Version min et max de la spécification Windows Sockets
    WSADATA wsaData;							// Informations sur l’implémentation de Windows Sockets

    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err)
    {
        printf("Erreur WSAStartup : %d\n", err);
        return false;
    }
    else
        return true;
}

bool NetWork::CreateSocket()
{
    mConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mConnectSocket == INVALID_SOCKET)
    {
        printf("Erreur Socket : %d\n", WSAGetLastError());
        WSACleanup();
        return false;
    }
    else
        return true;
}

sockaddr_in NetWork::SettingProtocol()
{
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_port = htons(PORT);
    inet_pton(AF_INET, ADRESSE, &clientService.sin_addr);// Convertit une adresse réseau IPv4 ou IPv6 en une forme binaire numérique
    return clientService;
}

bool NetWork::ConnectServer(sockaddr_in& clientService)
{
    if (connect(mConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService)))
    {
        printf("Erreur connect() %d\n", WSAGetLastError());
        Close();
        return false;
    }
    else
    {
        printf("connexion au serveur reussite\n");
        return true;
    }
}

bool NetWork::SendRequest(const char* sendBuffer)
{
    const size_t sendBufferSize = 0;// TO DO

    if (send(mConnectSocket, sendBuffer, sendBufferSize, 0) == SOCKET_ERROR)
    {
        printf("Erreur send() %d\n", WSAGetLastError());
        Close();
        return false;
    }
    else
        return true;
}

char* NetWork::Recieve()
{
    char* recieveBuffer = nullptr;
    const size_t recieveBufferSize = 0;// TO DO

    int iResult = recv(mConnectSocket, recieveBuffer, recieveBufferSize, 0);
    if (iResult <= 0)
    {
        if (iResult == 0)
            printf("connexion fermee\n");
        else
            printf("Erreur recv() : %d\n", WSAGetLastError());

        Close();
    }

    return recieveBuffer;
}

void NetWork::Close()
{
    int close = closesocket(mConnectSocket);

    if (close == SOCKET_ERROR)
        printf("Erreur fermeture socket : %d\n", close);
    else
        printf("Socket ferme\n");

    WSACleanup();
}
