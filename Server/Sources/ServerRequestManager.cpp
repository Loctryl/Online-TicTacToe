#include "Headers/ServerRequestManager.h"
#include "..\Headers\ServerNetWork.h"

ServerRequestManager* ServerRequestManager::mInstance = nullptr;

ServerRequestManager::ServerRequestManager() { mNetWork = new ServerNetWork(); }

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
    return ((ServerNetWork*)mNetWork)->Init();
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
    case play:// Le serveur recoit le coup d'un joueur
        printf("Coordonnee Recue\n");
        int Coords[2] = { parsedMessage["x"], parsedMessage["y"] };
        bool validation = true;//game.play(Coords[0], Coords[1])
        SendRequestValidation(validation);

        if (validation)
        {
            NextClient();

            if (!SendRequestPlay(Coords))
                return false;
        }

        break;

    //case connection:
    //    // Attribute ID
    //    SendRequestPlayer(1); // A changer
    //    printf("Sent Player Number to Player\n");
    //    NextClient();
    //    break;

    default:
        printf("Reception event incorrect : EventMessage %s\n", MessageType);
        break;
    }

    return true;
}

void ServerRequestManager::NextClient() const
{
    ((ServerNetWork*)mNetWork)->NextClient();
}
