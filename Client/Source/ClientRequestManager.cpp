#include "Headers/ClientRequestManager.h"
#include "Headers/ClientNetWork.h"
#include <iostream>

ClientRequestManager::ClientRequestManager() : mNetWork(new ClientNetWork()) { }

bool ClientRequestManager::Init() { return mNetWork->Init(); }

bool ClientRequestManager::Receive(std::string request)
{
    json parsedMessage = json::parse(request);

    std::string type = parsedMessage["type"].dump();
    if (type == "play")
        return ReceivePlay(parsedMessage);
    else if (type == "validation")
        return ReceiveValidation(parsedMessage);
    else if (type == "start")
        return ReceiveStart(parsedMessage);

}

bool ClientRequestManager::SendRequest(int coord[2])
{
    json data = {
        {"type", "play"},
        {"x", coord[0]},
        {"y", coord[1]}
    };

    return mNetWork->SendRequest(data.dump().c_str());
}

bool ClientRequestManager::ReceiveValidation(json parsedMessage)
{
    if (parsedMessage["answer"]) {
        //return game.validateMove(true);
    }
    //game.validateMove(false);
    printf("validation recue\n");

    return false;
}

bool ClientRequestManager::ReceivePlay(json parsedMessage)
{
    //return game.play(parsedMessage["x"], parsedMessage["y"]);
    return true;
}

bool ClientRequestManager::ReceiveStart(json parsedMessage)
{
    //game.start(parsedMessage["player"],parsedMessage["enemyNickname"])
    return false;
}

bool ClientRequestManager::Close() { return mNetWork->Close(); }
