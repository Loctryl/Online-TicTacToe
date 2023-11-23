#include "RequestManager.h"
#include "Utility/Network/Network.h"
#include "Utility/Resources/utilities.h"
#include "Utility/Thread/Thread.h"

RequestManager::~RequestManager() { REL_PTR(mNetWork) }

int RequestManager::EventToInt(std::string event)
{
    if (event == "play")
        return play;
    if (event == "validation")
        return validation;
    if (event == "winner")
        return winner;
    if (event == "join")
        return join;
    if(event == "leave")
        return leave;
   /* else if (event == "notif")
        return notif;
    else if (event == "player")
        return player;*/
    else// if (event == "connect")
        return -1;
}

bool RequestManager::SendRequestPlay(int coord[2], SOCKET* socket) const
{
    json data = {
        {"type", "play"},
        {"x", coord[0]},
        {"y", coord[1]}
    };

    return mNetWork->SendRequest(data.dump(), socket);
}

bool RequestManager::SendRequestJoin(SOCKET* socket, string nickname, int playerNum) const
{
    json data = {
        {"type", "join"},
        {"nickname", nickname},
        {"player", playerNum}
    };

    return mNetWork->SendRequest(data.dump(), socket);
}

bool RequestManager::SendRequestLeave(SOCKET* socket) const
{
    json data = {
        {"type", "leave"},
    };

    return mNetWork->SendRequest(data.dump(), socket);
}

std::string RequestManager::Recieve(SOCKET* socket)
{
    return mNetWork->Recieve(socket);
}

bool RequestManager::Close() const
{
    return mNetWork->Close();
}
