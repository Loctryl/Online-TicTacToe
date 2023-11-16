#pragma once
#include <string>
#include <Headers/json.hpp>

using json = nlohmann::json;

class ClientNetWork;

class ClientRequestManager
{
public:
    ClientRequestManager();
    virtual ~ClientRequestManager() = default;

    bool Init();

    bool Receive(std::string request);
    bool SendRequest(int coord[2]);

    bool ReceiveValidation(json parsedMessage);
    bool ReceivePlay(json parsedMessage);
    bool ReceiveStart(json parsedMessage);

    bool Close();

private:
    ClientNetWork* mNetWork;
};
