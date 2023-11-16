#pragma once
#include <WinSock2.h>
#include <string>

class ClientNetWork
{
public:
    ClientNetWork();
    ~ClientNetWork();

    bool Init();

    bool SendRequest(std::string data);
    std::string Recieve();
    bool Close();
    
private:
    SOCKET mConnectSocket = {};

    bool SettingSocket();
    bool CreateSocket();
    sockaddr_in SettingProtocol();
    bool ConnectServer(sockaddr_in& clientService);
};
