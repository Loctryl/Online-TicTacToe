#pragma once
#include <string>
#include "Utility/json.hpp"

using json = nlohmann::json;

class Network;

enum EventMessage
{
    choice, play, validation, notif, player, connection
};

class RequestManager
{
public:
    ~RequestManager();

    bool GameIsEnded();

    virtual bool Init() = 0;

    bool SendRequestPlay(int coord[2]) const;

    std::string Recieve();
    bool Close() const;

protected:
    Network* mNetWork;
    bool mEndGame = false;

    int EventToInt(std::string event);
};