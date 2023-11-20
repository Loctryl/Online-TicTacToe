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

    bool SendRequest(std::string data);
    bool AcceptClient(SOCKET* socket);
    std::string Recieve();

    bool Close();

    void NextClient();

private:
    SOCKET mListenSocket = {};
    SOCKET mAcceptSocket[NB_CLIENT] = {};
    int mActualClient = 0;
    
    bool Bind(sockaddr_in& serviceServer);// Associe une adresse IP et un numero de port à un socket
    bool WaitClients();
};
