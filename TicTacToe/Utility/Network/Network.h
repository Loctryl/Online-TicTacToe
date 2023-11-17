#pragma comment(lib, "Ws2_32.lib")

#pragma once
#include <string>
#include <WinSock2.h>

class Network
{
public:
    Network() = default;
    ~Network() = default;

    virtual bool Close() = 0;

    bool Init(SOCKET &sock);
    sockaddr_in SettingProtocol();
    
    bool SendRequest(SOCKET &sock, std::string data);
    std::string Receive(SOCKET &sock);
    bool CloseSocket(SOCKET &sock);

private:
    bool SettingSocket();
    bool CreateSocket(SOCKET &sock);

    bool ErrorRecv(int& iResult);
};