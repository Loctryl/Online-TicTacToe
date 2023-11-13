#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define PORT "80"
#define ADRESS "localhost"
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
    void Recieve();
    
private:
    WSADATA mWsaData;
    SOCKET mConnectSocket;
    addrinfo* mPtr;
};
