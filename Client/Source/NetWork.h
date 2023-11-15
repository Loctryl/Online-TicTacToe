#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 6666
#define ADRESSE "127.0.0.1"

class NetWork
{
public:
    NetWork();
    ~NetWork();

    bool Init();
    bool SettingSocket();
    bool CreateSocket();
    sockaddr_in SettingProtocol();
    bool ConnectServer(sockaddr_in& clientService);


    bool SendRequest(const char *sendBuffer);
    char* Recieve();
    
private:
    SOCKET mConnectSocket;

    void Close();
};
