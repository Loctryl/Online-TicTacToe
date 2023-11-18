#include "RequestManager.h"
#include "Utility/Network/Network.h"

RequestManager::~RequestManager() {
    delete mNetWork;
}

int RequestManager::EventToInt(std::string event)
{
    if (event == "play")
        return play;
    else if (event == "notif")
        return notif;
    else if (event == "answer")
        return answer;
    else if (event == "player")
        return player;
    else// if (event == "connect")
        return connection;
}

std::string RequestManager::Recieve()
{
    return mNetWork->Recieve();
}

bool RequestManager::Close() const
{
    return mNetWork->Close();
}
