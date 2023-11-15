#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define PORT "80"
#define ADRESS "google.com"
#define DEFAULT_BUFFER_LENGTH 512


class NetWork
{
public:
    NetWork();
    ~NetWork();

    void Init();
    void CreateSocket();
    bool ConnectServer();
    void SendRequest(const char *sendBuffer);
    std::string Recieve();
    
private:
    WSADATA mWsaData;
    SOCKET mConnectSocket;
    addrinfo* mPtr;
};
