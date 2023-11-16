#pragma once
#include <WinSock2.h>
#include <string>

class NetWork
{
public:
    NetWork();
    ~NetWork();

    bool Init();

    bool SendRequest(const char* data);
    std::string Recieve();
    bool Close();
    
private:
    SOCKET mConnectSocket = {};

    bool SettingSocket();
    bool CreateSocket();
    sockaddr_in SettingProtocol();
    bool ConnectServer(sockaddr_in& clientService);
};
