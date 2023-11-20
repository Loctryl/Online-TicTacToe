#include "Headers/ServerRequestManager.h"
#include "..\Headers\ServerNetWork.h"

ServerRequestManager::ServerRequestManager() : mNetWork(new ServerNetWork()) { }

bool ServerRequestManager::Init()
{
    return mNetWork->Init() && mNetWork->WebInit();
}

bool ServerRequestManager::SendRequestAnswer(bool validation) const
{
    json data = {
        {"type", "answer"},
        {"answer", validation}
    };

    return mNetWork->SendRequest(data.dump());
}

bool ServerRequestManager::SendRequestPlay(int coord[2]) const
{
    json data = {
        {"type", "play"},
        {"x", coord[0]},
        {"y", coord[1]}
    };

    return mNetWork->SendRequest(data.dump());
}



bool ServerRequestManager::SendRequestNotif(std::string Message) const
{
    json data = {
        {"type", "notif"},
        {"content", Message.c_str()}
    };

    return mNetWork->SendRequest(data.dump());
}

bool ServerRequestManager::SendRequestPlayer(int number)
{
    json data = {
    {"type", "player"},
    {"number", number}
    };

    return mNetWork->SendRequest(data.dump());
}

bool ServerRequestManager::RecievePlay(json Message, int* coord)
{
    coord[0] = Message["x"];
    coord[1] = Message["y"];

    return true;
}

bool ServerRequestManager::ManageMessage(std::string Message)
{
    json parsedMessage = json::parse(Message);
    std::string MessageType = parsedMessage["type"];
    if (MessageType == "play") {
        int Coords[2];
        if (!RecievePlay(parsedMessage, Coords)) {
            printf("Erreur lors de la réception de Coordonnées\n");
            return false;
        }
        //game.play(Coords) -> returns if Coords is playable or not
        bool IsPlayable = true; // A remplacer
        printf("Coordonnee Recue\n");

        SendRequestAnswer(IsPlayable);
        if (IsPlayable) {
            // Si le move finit la partie -> Endgame
            NextClient();
            SendRequestPlay(Coords);
        }
    }
    else if (MessageType == "notif") {
        // do something
    }
    else if (MessageType == "answer") {
        printf("this shouldn't happen\n");
    }
    else if (MessageType == "player") {
        printf("this shouldn't happen\n");
    }
    else if (MessageType == "connect") {
        // Attribute ID
        SendRequestPlayer(1); // A changer
        printf("Sent Player Number to Player\n");
        NextClient();
    }
    return true;
}

std::string ServerRequestManager::Recieve()
{
    return mNetWork->Recieve();
}

bool ServerRequestManager::Close() const
{
    return mNetWork->Close();
}

void ServerRequestManager::NextClient() const
{
    mNetWork->NextClient();
}
