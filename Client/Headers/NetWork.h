#pragma once
#include <WinSock2.h>

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
