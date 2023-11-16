#include "Headers/ClientRequestManager.h"
#include <Headers/json.hpp>
#include "Headers/ClientNetWork.h"
#include <iostream>

using json = nlohmann::json;

ClientRequestManager::ClientRequestManager() : mNetWork(new ClientNetWork()) { }

bool ClientRequestManager::Init() { return mNetWork->Init(); }

bool ClientRequestManager::SendRequest(int coord[2])
{
    json data = {
        {"type", "play"},
        {"x", coord[0]},
        {"y", coord[1]}
    };

    return mNetWork->SendRequest(data.dump());
}

bool ClientRequestManager::RecieveValidation(bool& validation)
{
    std::string data = mNetWork->Recieve();

    /*if (data == nullptr)
        return false;*/

    json parsedMessage = json::parse(data);
    validation = parsedMessage["answer"];

    printf("validation recue\n");
    return true;
}

bool ClientRequestManager::RecievePlay(int coord[2])
{
    std::string data = mNetWork->Recieve();

    /*if (data == nullptr)
        return false;*/

    json parsedMessage = json::parse(data);
    coord[0] = parsedMessage["x"];
    coord[1] = parsedMessage["y"];

    printf("deplacement recue\n");
    return true;
}

bool ClientRequestManager::Close() { return mNetWork->Close(); }
