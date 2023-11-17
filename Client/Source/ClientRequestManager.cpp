#include "Headers/ClientRequestManager.h"
#include "Headers/ClientNetWork.h"
#include <iostream>

ClientRequestManager* ClientRequestManager::mInstance = nullptr;

ClientRequestManager::ClientRequestManager() { mNetWork = new ClientNetWork(); }

ClientRequestManager::~ClientRequestManager() {
    delete mNetWork;
}

ClientRequestManager* ClientRequestManager::GetInstance()
{
    if (mInstance != nullptr) return mInstance;
    mInstance = new ClientRequestManager();
    return mInstance;
}

bool ClientRequestManager::Init() { return mNetWork->Init(); }

bool ClientRequestManager::SendRequestPlay(int coord[2]) const
{
    json data = {
        {"type", "play"},
        {"x", coord[0]},
        {"y", coord[1]}
    };

    return mNetWork->SendRequest(data.dump());
}



bool ClientRequestManager::SendRequestNotif(std::string Message) const
{
    json data = {
        {"type", "notif"},
        {"content", Message.c_str()}
    };

    return mNetWork->SendRequest(data.dump());
}

bool ClientRequestManager::RecievePlay(json Message, int* coord)
{
    coord[0] = Message["x"];
    coord[1] = Message["y"];

    return true;
}

bool ClientRequestManager::RecieveAnswer(json Message, bool* Answer)
{
    bool tempanswer = Message["answer"];
    Answer = &tempanswer;

    return true;
}

bool ClientRequestManager::RecieveNotif(json Message, std::string* Notif)
{
    *Notif = Message["notif"];

    return true;
}

bool ClientRequestManager::ManageMessage(std::string Message)
{
    json parsedMessage = json::parse(Message);
    std::string MessageType = parsedMessage["type"];
    if (MessageType == "play") {
        // My Turn = true
        int Coords[2];
        if (!RecievePlay(parsedMessage, Coords)) {
            printf("Error : Couldn't Recieve Coords properly\n");
            return false;
        }
        // game.play(coords)
        // Update game
        // Event Input
        // Send l'input au serveur
        Coords[0] = 0; // A changer
        Coords[1] = 1; // A changer
        SendRequestPlay(Coords);
    }
    else if (MessageType == "notif") {
        // do something
    }
    else if (MessageType == "answer") {
        bool validation =  false;
        if (!RecieveAnswer(parsedMessage, &validation)) {
            printf("Error : Couldn't Recieve Answer properly\n");
            return false;
        }
        if (!validation) {
            int Coords[2];
            // On rejoue
            Coords[0] = 0; // A changer
            Coords[1] = 1; // A changer
            SendRequestPlay(Coords);
        }
        else {
            // My Turn = false
            // On attend que l'autre joueur ait joué ou endgame.
        }
    }
    else if (MessageType == "player") {
        // Struct player : player number = ce qu'on a reçu
    }
    else if (MessageType == "connect") {
        printf("this souldn't happen\n");
    }
    return true;
}

std::string ClientRequestManager::Recieve()
{
    return mNetWork->Recieve();
}

bool ClientRequestManager::Close() const
{
    return mNetWork->Close();
}
