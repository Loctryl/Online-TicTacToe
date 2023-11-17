#pragma comment(lib, "Ws2_32.lib")

#pragma once
#include "Utility/Network/Network.h"

class ClientNetWork : public Network
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
    
    bool ConnectServer(sockaddr_in& clientService);
};
