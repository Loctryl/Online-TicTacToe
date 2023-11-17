#pragma once

#include <string>
#include "json.hpp"

using json = nlohmann::json;

class ServerNetWork;

class ServerRequestManager
{
public:
    ~ServerRequestManager();

    static ServerRequestManager* GetInstance();

    bool Init();
    bool SendRequestPlayer(int number);
    bool SendRequestAnswer(bool validation) const;
    bool SendRequestPlay(int coord[2]) const;
    bool SendRequestNotif(std::string Message) const;
    bool RecievePlay(json Message, int* coord);
    std::string Recieve();
    bool Close() const;
    void NextClient() const;

    bool ManageMessage(std::string Message);

private:
    static ServerRequestManager* mInstance;

    ServerRequestManager();
    ServerNetWork* mNetWork;
};
