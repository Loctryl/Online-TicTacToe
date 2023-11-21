#pragma once
#include <string>
#include "Resources/framework.h"

class Network
{
public:
    Network() = default;
    ~Network() = default;

    virtual bool Close() = 0;


    virtual bool Init() = 0;

    virtual bool SendRequest(std::string data, SOCKET* socket) = 0;
    virtual std::string Recieve(SOCKET* socket) = 0;

    
    bool CloseSocket(SOCKET &sock);
    bool SendToWeb(SOCKET& sock, std::string data);

protected:
    bool Init(SOCKET& sock);
    sockaddr_in SettingProtocol();
    sockaddr_in SettingWebProtocol();

    bool SendRequest(SOCKET& sock, std::string data);
    std::string Receive(SOCKET* sock);

private:
    bool SettingSocket();
    bool CreateSocket(SOCKET &sock);

    bool ErrorRecv(int& iResult);
};