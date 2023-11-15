#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <Headers/json.hpp>

using json = nlohmann::json;

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

    bool SendRequest(int x, int y);
    json Recieve();
    void Close();
    
private:
    SOCKET mConnectSocket = {};

    bool SettingSocket();
    bool CreateSocket();
    sockaddr_in SettingProtocol();
    bool ConnectServer(sockaddr_in& clientService);
};
