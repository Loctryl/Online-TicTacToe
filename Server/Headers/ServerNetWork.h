#pragma once
#include <WinSock2.h>
#include <string>


#define NB_CLIENT 2

class ServerNetWork
{
public:
    ServerNetWork();
    ~ServerNetWork();

    bool Init();

    bool SendRequest(const char* data);
    std::string Recieve();
    bool Close();
    void NextClient();

private:
    SOCKET mListenSocket = {};
    SOCKET mAcceptSocket[NB_CLIENT];
    int mActualClient = 0;

    bool SettingSocket();
    bool CreateSocketServer();
    sockaddr_in SettingProtocol();
    
    bool Bind(sockaddr_in& serviceServer);// Associe une adresse IP et un numero de port à un socket
    bool WaitClients();
    bool AcceptClient(int& numClient);
    bool CloseClient(int& numClient);
    bool CloseServer();
};
