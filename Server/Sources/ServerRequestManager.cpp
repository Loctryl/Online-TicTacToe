#include "Headers/ServerRequestManager.h"
#include "..\Headers\ServerNetWork.h"

ServerRequestManager* ServerRequestManager::mInstance = nullptr;

ServerRequestManager::ServerRequestManager() { mNetWork = new ServerNetWork(); }

int ServerRequestManager::EventToInt(std::string event)
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

ServerRequestManager::~ServerRequestManager() {
    delete mNetWork;
}

ServerRequestManager* ServerRequestManager::GetInstance()
{
    if (mInstance != nullptr) return mInstance;
    mInstance = new ServerRequestManager();
    return mInstance;
}


bool ServerRequestManager::Init()
{
    return mNetWork->Init();
}

bool ServerRequestManager::SendRequestChoice(int coord[2]) const
{
    json data = {
        {"type", "choice"},
        {"x", coord[0]},
        {"y", coord[1]}
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

bool ServerRequestManager::SendRequestValidation(bool validation) const
{
    json data = {
        {"type", "validation"},
        {"answer", validation}
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

    switch (EventToInt(MessageType))
    {
    case choice:
        int Coords[2] = { parsedMessage["x"], parsedMessage["y"] };
        if (!SendRequestChoice(Coords))
        {
            Close();
            return false;
        }
        break;

    case play:
        int Coords[2] = { parsedMessage["x"], parsedMessage["y"] };
        //game.play(Coords)
        printf("Coordonnee Recue\n");
        break;

    case validation:
        bool validation = parsedMessage["answer"];

        if (validation)
        {
            printf("Choix valide\n");
            //game.play(Coords)
        }
        break;

    case notif:
        // do something
        break;

    case player:
        printf("this shouldn't happen\n");
        break;

    case connection:
        // Attribute ID
        SendRequestPlayer(1); // A changer
        printf("Sent Player Number to Player\n");
        NextClient();
        break;

    default:
        break;
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
