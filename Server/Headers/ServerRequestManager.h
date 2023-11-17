#pragma once

#include <string>
#include "json.hpp"

using json = nlohmann::json;

class ServerNetWork;

enum EventMessage
{
    choice, play, validation, notif, player, connection
};

class ServerRequestManager
{
public:
    ~ServerRequestManager();

    static ServerRequestManager* GetInstance();

    bool Init();
    std::string Recieve();
    bool Close() const;
    void NextClient() const;

    bool ManageMessage(std::string Message);

private:
    static ServerRequestManager* mInstance;

    ServerRequestManager();
    ServerNetWork* mNetWork;

    int EventToInt(std::string event);


    bool SendRequestChoice(int coord[2]) const;
    bool SendRequestPlay(int coord[2]) const;
    bool SendRequestValidation(bool validation) const;

    bool SendRequestPlayer(int number);
    bool SendRequestNotif(std::string Message) const;
    bool RecievePlay(json Message, int* coord);
};
