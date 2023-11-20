#pragma once
#include <string>

#include "Resources/framework.h"
#include "Utility/json.hpp"
#include "Resources/utilities.h"


using json = nlohmann::json;

class Network;

enum EventMessage
{
    choice, play, validation, notif, player, connection
};

class RequestManager
{
public:
    virtual ~RequestManager();

    inline bool GameIsEnded() const { return mEndGame; }

    virtual bool Init() = 0;

    bool SendRequestPlay(int coord[2], SOCKET* socket) const;

    std::string Recieve(SOCKET* socket);
    bool Close() const;

protected:
    Network* mNetWork;
    bool mEndGame = false;

    int EventToInt(std::string event);
};