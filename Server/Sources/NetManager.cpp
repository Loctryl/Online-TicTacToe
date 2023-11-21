#include "Headers/NetManager.h"
#include "Grid/Grid.h"
#include "Grid/Player.h"

NetManager* NetManager::mInstance = nullptr;

NetManager::NetManager() {  }

NetManager::~NetManager() {  }

NetManager* NetManager::GetInstance()
{
    if (mInstance == nullptr)
        mInstance = new NetManager();
    return mInstance;
}

Grid* NetManager::CreateGame()
{
    Grid* game = new Grid;
    mGames.push_back(game);
    return game;
}

void NetManager::CreatePlayer(SOCKET* sock, std::string name)
{
    Player* p = new Player();
    p->mSocket = sock;
    p->mId = SetNewID();
    p->mNickName = name;
    if(mWaitingGame)
    AddPlayerToGame(p);
    mPlayers.push_back(p);
}

void NetManager::SetPlayerNickname(SOCKET* sock, std::string name)
{
    for (auto player : mPlayers)
    {
        if (player->mSocket == sock)
            player->mNickName = name;
    }
}

void NetManager::AddPlayerToGame(Player* p)
{
    if(mWaitingGame)
    {
        mWaitingGame->mPlayers[1] = p;
        p->mInGameId = 1;
    }
    else
    {
        mWaitingGame = CreateGame();
        mWaitingGame->mPlayers[0] = p;
        p->mInGameId = 0;
    }
    p->mCurrentGame = mWaitingGame;
}


Grid* NetManager::GetGameByPlayerId(int id) const
{
    for(auto game : mGames)
    {
        if(game->mPlayers[0]->mId == id || game->mPlayers[1]->mId == id)
            return game;
    }
    return nullptr;
}

Player* NetManager::GetPlayerBySocket(SOCKET* sock) const
{
    for(auto player : mPlayers)
    {
        if(player->mSocket == sock)
            return player;
    }
    return nullptr;
}

Player* NetManager::GetPlayerById(int id) const
{
    for (auto player : mPlayers)
    {
        if (player->mId == id)
            return player;
    }
    return nullptr;
}

Player* NetManager::GetEnemyPlayer(SOCKET* sock)
{
    Player* player = GetPlayerBySocket(sock);
    return GetEnemyPlayer(player->mId);
}

Player* NetManager::GetEnemyPlayer(int id)
{
    Grid* game = GetGameByPlayerId(id);
    for (auto player : game->mPlayers) {
        if (player->mId != id)
            return player;
    }
}

std::vector<Grid*> NetManager::GetGames()
{
    return mGames;
}

int NetManager::SetNewID()
{
    mCurrentId++;
    return mCurrentId;
}



