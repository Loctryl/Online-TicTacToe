#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 6666
#define ADRESSE "127.0.0.1"

#define PACKET_SIZE 2048

class NetWork
{
public:
    NetWork();
    ~NetWork();

    bool Init();

    bool SendRequest(const char* data);
    char* Recieve();
    bool Close();
    
private:
    SOCKET mConnectSocket = {};

    bool SettingSocket();
    bool CreateSocket();
    sockaddr_in SettingProtocol();
    bool ConnectServer(sockaddr_in& clientService);
};
