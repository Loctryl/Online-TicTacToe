#pragma once
#include "framework.h"
#include "Utility/Network/Network.h"

class WebNetWork : public Network
{
public:
    WebNetWork();
    ~WebNetWork() = default;

    bool Init();

    bool SendRequest(std::string data, SOCKET* socket);
    bool AcceptWebClient(SOCKET* socket);
    std::string Recieve(SOCKET* socket);

    bool Close();

private:
    SOCKET mWebSocket = {};

    bool Bind(sockaddr_in& serviceServer, SOCKET* socket);
    bool WaitWebClients();
};

