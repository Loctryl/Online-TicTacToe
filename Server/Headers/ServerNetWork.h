#pragma once
#include "framework.h"
#include "Utility/Network/Network.h"

#define NB_CLIENT 2

class ServerNetWork : public Network
{
public:
    ServerNetWork();
    ~ServerNetWork() = default;

    bool Init();

    bool SendRequest(std::string data, SOCKET* socket);
    bool AcceptClient(SOCKET* socket);
    std::string Recieve(SOCKET* socket);

    bool Close();

private:
    SOCKET mListenSocket = {};
    
    bool Bind(sockaddr_in& serviceServer, SOCKET* socket);// Associe une adresse IP et un numero de port à un socket
    bool WaitClients();
};
