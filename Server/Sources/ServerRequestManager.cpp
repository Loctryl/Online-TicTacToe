#include "Headers/ServerRequestManager.h"
#include "Headers/ServerNetWork.h"
#include "Headers/WebNetWork.h"
#include "Headers/NetManager.h"
#include "Grid/Player.h"
#include "Grid/Grid.h"
#include "Resources/utilities.h"

ServerRequestManager* ServerRequestManager::mInstance = nullptr;

ServerRequestManager::ServerRequestManager() { mNetWork = new ServerNetWork(); mWebNetWork = new WebNetWork(); }

ServerRequestManager::~ServerRequestManager() {
    REL_PTR(mNetWork)
}

bool ServerRequestManager::Init()
{
    return ((ServerNetWork*)mNetWork)->Init() && ((WebNetWork*)mWebNetWork)->Init();
}

ServerRequestManager* ServerRequestManager::GetInstance()
{
    if (mInstance != nullptr) return mInstance;
    mInstance = new ServerRequestManager();
    return mInstance;
}

bool ServerRequestManager::SendToWeb(std::string request, SOCKET* socket) const
{
    return mNetWork->SendToWeb(*socket, request);
}

bool ServerRequestManager::SendRequestValidation(bool validation, SOCKET* socket) const
{
    json data = {
        {"type", "validation"},
        {"answer", validation}
    };

    return mNetWork->SendRequest(data.dump(), socket);
}

bool ServerRequestManager::SendRequestWinner(int winner, SOCKET* socket) const
{
    json data = {
        {"type", "winner"},
        {"winner", winner}
    };

    return mNetWork->SendRequest(data.dump(), socket);
}

bool ServerRequestManager::ManageMessage(std::string Message, SOCKET* socket)
{
    json parsedMessage = json::parse(Message);
    std::string MessageType = parsedMessage["type"];

    NetManager* net = NetManager::GetInstance();

    Player* player = net->GetPlayerBySocket(socket);
    Grid* grid = player->mCurrentGame;

    switch (EventToInt(MessageType))
    {
        case play:
        {
            // Le serveur recoit le coup d'un joueur
            if (grid->mPlayers[1] == nullptr || player->mInGameId != grid->mTurnPlayer)
                break;

            printf("Coordonnee Recue\n");
            int Coords[2] = { parsedMessage["x"], parsedMessage["y"] };

            bool validation = (grid->GetValue(Coords[0], Coords[1]) == -1);

            if (!SendRequestValidation(validation, socket))
                return false;

            if (validation)
            {
                grid->Play(Coords[0],Coords[1]);

                if (!SendRequestPlay(Coords, NetManager::GetInstance()->GetEnemyPlayer(socket)->mSocket))
                    return false;
            }
            int win = grid->IsWinner();
            if (win != -1) {
                SendRequestWinner(win,socket);
                SendRequestWinner(win,NetManager::GetInstance()->GetEnemyPlayer(socket)->mSocket);
                cout << "Game over ! The winner is player : " << grid->mTurnPlayer << endl;
            } else
                grid->mTurnPlayer = (grid->mTurnPlayer + 1) % 2;
            
            break;
        }
        case join:
        {
            NetManager::GetInstance()->AddPlayerToGame(player);
            SendRequestJoin(socket);
            break;
        }
        case leave:
        {
            grid->mPlayers[player->mInGameId] = nullptr;
            player->mCurrentGame = nullptr;
            if(!grid->mPlayers[0] && !grid->mPlayers[1])
                NetManager::GetInstance()->DeleteGame(grid->mGameId);
            SendRequestLeave(socket);
            break;
        }
        default:
            printf("Reception event incorrect : EventMessage %s\n", MessageType);
            break;
    }
    return true;
}