#include "Headers/RequestManager.h"
#include <Headers/json.hpp>
#include "Headers/NetWork.h"
#include <iostream>

using json = nlohmann::json;

RequestManager::RequestManager() : mNetWork(new NetWork()) { }

bool RequestManager::Init() { return mNetWork->Init(); }

bool RequestManager::SendRequest(int coord[2])
{
    json data = {
        {"type", "play"},
        {"x", coord[0]},
        {"y", coord[1]}
    };

    return mNetWork->SendRequest(data.dump().c_str());
}

bool RequestManager::RecieveValidation(bool& validation)
{
    std::string data = mNetWork->Recieve();

    /*if (data == nullptr)
        return false;*/

    json parsedMessage = json::parse(data);
    validation = parsedMessage["answer"];

    printf("validation recue\n");
    return true;
}

bool RequestManager::RecievePlay(int coord[2])
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

bool RequestManager::Close() { return mNetWork->Close(); }
