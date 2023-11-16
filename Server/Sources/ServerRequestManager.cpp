#include "Headers/ServerRequestManager.h"
#include <Headers/json.hpp>
#include "..\Headers\ServerNetWork.h"
#include <string>

using json = nlohmann::json;

ServerRequestManager::ServerRequestManager() : mNetWork(new ServerNetWork()) { }

bool ServerRequestManager::Init()
{
    return mNetWork->Init();
}

bool ServerRequestManager::SendRequest(bool validation) const
{
    json data = {
        {"type", "answer"},
        {"answer", validation}
    };

    return mNetWork->SendRequest(data.dump());
}

bool ServerRequestManager::SendRequest(int coord[2]) const
{
    json data = {
        {"type", "play"},
        {"x", coord[0]},
        {"y", coord[1]}
    };

    return mNetWork->SendRequest(data.dump());
}

bool ServerRequestManager::RecievePlay(int coord[2])
{
    std::string data = mNetWork->Recieve();

    if (data == "")
        return false;

    //if (donnée invalide) TO DO : vérification réception
        //return false;

    json parsedMessage = json::parse(data);
    coord[0] = parsedMessage["x"];
    coord[1] = parsedMessage["y"];

    printf("deplacement recue\n");
    return true;
}

bool ServerRequestManager::Close() const
{
    return mNetWork->Close();
}

void ServerRequestManager::NextClient() const
{
    mNetWork->NextClient();
}
