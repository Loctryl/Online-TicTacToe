#include "Headers/RequestManager.h"
#include <Headers/json.hpp>
#include "Headers/NetWork.h"

using json = nlohmann::json;

RequestManager::RequestManager() : mNetWork(new NetWork()) { }

bool RequestManager::Init() { return mNetWork->Init(); }

bool RequestManager::SendRequest(bool validation) const
{
    json data = {
        {"answer", validation}
    };

    return mNetWork->SendRequest(data.dump().c_str());
}

bool RequestManager::SendRequest(int coord[2]) const
{
    json data = {
        {"x", coord[0]},
        {"y", coord[1]}
    };

    return mNetWork->SendRequest(data.dump().c_str());
}

bool RequestManager::RecievePlay(int coord[2])
{
    std::string data = mNetWork->Recieve();

    /*if (data == nullptr)
        return false;*/

    //if (donnée invalide) TO DO : vérification réception
        //return false;

    json parsedMessage = json::parse(data);
    coord[0] = parsedMessage["x"];
    coord[1] = parsedMessage["y"];

    printf("deplacement recue\n");
    return true;
}

bool RequestManager::Close() { return mNetWork->Close(); }

void RequestManager::NextClient()
{
    mNetWork->NextClient();
}
