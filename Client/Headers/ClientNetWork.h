#pragma once
#include "../Ressources/framework.h"
#include "Utility/Network/Network.h"

class ClientNetWork : public Network
{
public:
    ClientNetWork();
    ~ClientNetWork();

    bool Init() override;
    bool ConnectServer();

    bool SendRequest(std::string data, SOCKET* socket);
    std::string Recieve(SOCKET* socket);
    bool Close();

    inline SOCKET* GetClientSocket() { return &mConnectSocket; }
    
private:
    SOCKET mConnectSocket = {};
    
};
