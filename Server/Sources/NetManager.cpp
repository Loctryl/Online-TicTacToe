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
        if(game->mPlayers[0]->mInGameId == id || game->mPlayers[1]->mInGameId == id)
            return game;
    }
    return nullptr;
}

int NetManager::GetPlayerBySocket(SOCKET* sock) const
{
    for(auto player : mPlayers)
    {
        if(player->mSocket == sock)
            return player->mId;
    }
    return -1;
}



