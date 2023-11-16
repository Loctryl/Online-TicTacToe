#pragma once
#include <string>
#include <WinSock2.h>

#define NB_CLIENT 2

class Network
{
public:
    Network() = default;
    ~Network() = default;

    static bool InitAsClient(SOCKET sock);
    static bool InitAsServer(SOCKET sock);
    
    static bool SendRequest(SOCKET sock, std::string data);
    static std::string Receive(SOCKET sock);
    static bool CloseSocket(SOCKET sock);

private:
    static bool SettingSocket();
    static bool CreateSocket(SOCKET sock);
    static sockaddr_in SettingProtocol();
    
    static bool ConnectServer(SOCKET sock, sockaddr_in& clientService);
    
    static bool Bind(SOCKET sock, sockaddr_in& serviceServer);
    static bool WaitClients(SOCKET sock);
    static bool AcceptClient(SOCKET sockClient, SOCKET sockServer);
};