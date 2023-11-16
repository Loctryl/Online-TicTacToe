#pragma once
#include <string>
#include <WinSock2.h>

#define NB_CLIENT 2

class Network
{
public:
    Network();
    ~Network();

    bool InitAsClient();
    bool InitAsServer();
    
    bool SendRequest(const char* data);
    std::string Receive();
    bool CloseSocket();

private:
    bool SettingSocket();
    bool CreateSocket();
    sockaddr_in SettingProtocol();
    
    // Client using
    SOCKET mConnectSocket = {};
    bool ConnectServer(sockaddr_in& clientService);

    
    // Server using
    SOCKET mListenSocket = {};
    SOCKET mAcceptSocket[NB_CLIENT];
    int mActualClient = 0;
    bool Bind(sockaddr_in& serviceServer);
    bool WaitClients();
    bool AcceptClient(int& numClient);
    //bool CloseClient(int& numClient);
};