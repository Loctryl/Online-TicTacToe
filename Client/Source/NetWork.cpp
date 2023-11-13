#include "NetWork.h"
#include <iostream>

NetWork::NetWork()
{
}

NetWork::~NetWork()
{
    closesocket(mConnectSocket);
}

void NetWork::Init()
{
    WSAStartup(MAKEWORD(2, 2), &mWsaData);
    mPtr = NULL;
    CreateSocket();
    ConnectServer();
}

void NetWork::CreateSocket()
{
    addrinfo *result = NULL, hints;
    
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    
    // Resolve the server address and port
    const char adrress[] = ADRESS;
    const int iResult = getaddrinfo(adrress, PORT, &hints, &result);
    if (iResult != 0)
    {
        WSACleanup();
        std::cout << "CreateSocket -> getaddrinfo failed: " << iResult << std::endl;
        throw;
    }

    mConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    mPtr = result;

    // Create a SOCKET for connecting to server
    mConnectSocket = socket(mPtr->ai_family, mPtr->ai_socktype, mPtr->ai_protocol);

    if (mConnectSocket == INVALID_SOCKET)
    {
        WSACleanup();
        std::cout << "CreateSocket -> Error at socket(): " << WSAGetLastError() << std::endl;
        throw;
    }

    freeaddrinfo(result);
}

bool NetWork::ConnectServer()
{
    // Connect to server.
    int iResult = connect(mConnectSocket, mPtr->ai_addr, static_cast<int>(mPtr->ai_addrlen));
    if (iResult == SOCKET_ERROR)
    {
        closesocket(mConnectSocket);
        mConnectSocket = INVALID_SOCKET;
        std::cout << "connexion failed." << std::endl << "Try to reconnect..." << std::endl;
        WSACleanup();
        return false;
        
    }
    
    return true;
}

void NetWork::SendRequest(const char* sendBuffer)
{
    // Send an initial buffer
    int iResult = send(mConnectSocket, sendBuffer, (int) strlen(sendBuffer), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(mConnectSocket);
        WSACleanup();
    }
}

void NetWork::Recieve()
{
    int  recieveBufferLength = DEFAULT_BUFFER_LENGTH;
    char recieveBuffer[DEFAULT_BUFFER_LENGTH];
    int iResult;
    
    do
    {
        iResult = recv(mConnectSocket, recieveBuffer, recieveBufferLength, 0);
        for(auto c : recieveBuffer)
            std::cout << c;
    }while (iResult > 0);
}
