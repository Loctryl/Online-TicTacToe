#include "RequestManager.h"
#include "Utility/Network/Network.h"

RequestManager::~RequestManager() { REL_PTR(mNetWork) }

int RequestManager::EventToInt(std::string event)
{
    if (event == "play")
        return play;
    if (event == "validation")
        return validation;
    if (event == "winner")
        return winner;
   /* else if (event == "notif")
        return notif;
    else if (event == "player")
        return player;*/
    else// if (event == "connect")
        return connection;
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

std::string RequestManager::Recieve(SOCKET* socket)
{
    return mNetWork->Recieve(socket);
}

bool RequestManager::Close() const
{
    return mNetWork->Close();
}
