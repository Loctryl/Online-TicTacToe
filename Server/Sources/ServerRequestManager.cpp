#include "Headers/ServerRequestManager.h"
#include "Headers/ServerNetWork.h"
#include "Headers/NetManager.h"
#include "Grid/Player.h"
#include "Grid/Grid.h"

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

bool ServerRequestManager::SendRequestValidation(bool validation, SOCKET* socket) const
{
    json data = {
        {"type", "validation"},
        {"answer", validation}
    };

    return mNetWork->SendRequest(data.dump(), socket);
}

bool ServerRequestManager::ManageMessage(std::string Message, SOCKET* socket)
{
    json parsedMessage = json::parse(Message);
    std::string MessageType = parsedMessage["type"];

    cout << "read socket : " << socket << endl;

    NetManager* net = NetManager::GetInstance();

    Player* player = net->GetPlayerBySocket(socket);
    Grid* grid = player->mCurrentGame;

    switch (EventToInt(MessageType))
    {
    case play: 
    { // Le serveur recoit le coup d'un joueur
        if (grid->mPlayers[1] == nullptr || player->mInGameId != grid->mTurnPlayer)
            break;

        printf("Coordonnee Recue\n");
        int Coords[2] = { parsedMessage["x"], parsedMessage["y"] };

        bool validation = (grid->GetValue(Coords[0], Coords[1]) == -1);

        if (!SendRequestValidation(validation, socket))
            return false;

        if (validation)
        {
            grid->mMainGrid[Coords[0]][Coords[1]] = player->mInGameId;

            if (!SendRequestPlay(Coords, NetManager::GetInstance()->GetEnemyPlayer(socket)->mSocket))
                return false;
        }
        grid->mTurnPlayer = (grid->mTurnPlayer + 1) % 2;

    }
        break;
    default:
        printf("Reception event incorrect : EventMessage %s\n", MessageType);
        break;
    }

    return true;
}