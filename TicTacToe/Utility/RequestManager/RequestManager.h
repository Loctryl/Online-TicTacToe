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

    virtual bool Init() = 0;

    std::string Recieve();
    bool Close() const;

protected:
    Network* mNetWork;
    int EventToInt(std::string event);
};