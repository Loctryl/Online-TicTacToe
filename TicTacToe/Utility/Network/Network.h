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


    virtual bool Init() = 0;

    virtual bool SendRequest(std::string data) = 0;
    virtual std::string Recieve() = 0;

    
    bool CloseSocket(SOCKET &sock);

protected:
    bool Init(SOCKET& sock);
    sockaddr_in SettingProtocol();

    bool SendRequest(SOCKET& sock, std::string data);
    std::string Receive(SOCKET& sock);

private:
    bool SettingSocket();
    bool CreateSocket(SOCKET &sock);

    bool ErrorRecv(int& iResult);
};