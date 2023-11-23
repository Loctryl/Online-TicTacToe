#pragma once
#include <string>

#include "Resources/framework.h"
#include "Utility/json.hpp"


using json = nlohmann::json;

class Network;
class ThreadObj;

enum EventMessage
{
    play, validation, winner, join, leave
};

class RequestManager
{
public:
    virtual ~RequestManager();

    inline bool GameIsEnded() const { return mEndGame; }

    virtual bool Init(ThreadObj* thread) = 0;

    bool SendRequestPlay(int coord[2], SOCKET* socket) const;

    bool SendRequestJoin(SOCKET* socket) const;

    bool SendRequestLeave(SOCKET* socket) const;
    
    std::string Recieve(SOCKET* socket);
    bool Close() const;

protected:
    Network* mNetWork;
    Network* mWebNetWork;
    bool mEndGame = false;

    int EventToInt(std::string event);
};