#pragma once
#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "TicTacToe.lib")

#include "Network/Network.h"

#define NB_CLIENT 2

class ServerNetWork : public Network
{
public:
    ServerNetWork();
    ~ServerNetWork() = default;

    bool Init();
    bool WebInit();

    bool SendRequest(std::string data);
    std::string Recieve();

    bool Close();

    void NextClient();

private:
    SOCKET mListenSocket = {};
    SOCKET mWebSocket = {};
    SOCKET mAcceptSocket[NB_CLIENT] = {};
    int mActualClient = 0;
    
    bool Bind(sockaddr_in& serviceServer, SOCKET* socket);// Associe une adresse IP et un numero de port à un socket
    bool ConnectServer(sockaddr_in& serviceServer);
    bool WaitClients();
    bool AcceptClient(int& numClient);
};
