#include "Headers/ServerRequestManager.h"
#include "Headers/ServerNetWork.h"

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

bool ServerRequestManager::SendRequestValidation(bool validation) const
{
    json data = {
        {"type", "validation"},
        {"answer", validation}
    };

    return mNetWork->SendRequest(data.dump());
}

bool ServerRequestManager::ManageMessage(std::string Message)
{
    json parsedMessage = json::parse(Message);
    std::string MessageType = parsedMessage["type"];

    switch (EventToInt(MessageType))
    {
    case play:// Le serveur recoit le coup d'un joueur
        {
            printf("Coordonnee Recue\n");
            int Coords[2] = { parsedMessage["x"], parsedMessage["y"] };
            bool validation = true;//game.TestChoice(Coords[0], Coords[1])
            
            if (!SendRequestValidation(validation))
                return false;

            if (validation)
            {
                //game.Play(Coords[0], Coords[1])
                // MAJ EndGame

                NextClient();

                if (!SendRequestPlay(Coords))
                    return false;
            }
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
