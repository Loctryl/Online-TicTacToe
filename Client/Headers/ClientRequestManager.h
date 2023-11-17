#pragma once

#include <string>
#include "json.hpp"

using json = nlohmann::json;

class ClientNetWork;

class ClientRequestManager
{
public:
    ClientRequestManager();
    virtual ~ClientRequestManager() = default;

    bool Init();
    bool SendRequestPlay(int coord[2]) const;
    bool SendRequestNotif(std::string Message) const;
    bool RecievePlay(json Message, int* coord);
    bool RecieveNotif(json Message, std::string* Notif);
    bool RecieveAnswer(json Message, bool* Answer);
    std::string Recieve();
    bool Close() const;

    bool ManageMessage(std::string Message);

private:
    ClientNetWork* mNetWork;
};
