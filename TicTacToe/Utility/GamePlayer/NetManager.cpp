#include "NetManager.h"
#include "Grid/Grid.h"
#include "Grid/Player.h"

NetManager::NetManager() {  }

NetManager::~NetManager() {  }

void NetManager::AddGame(Grid* game)
{
    mGames.push_back(game);
}


Grid* NetManager::GetGameByPlayerId(int id) const
{
    for(auto game : mGames)
    {
        if(game->mPlayers[0] == id || game->mPlayers[1] == id)
            return game;
    }
    return nullptr;
}

int NetManager::GetPlayerBySocket(SOCKET sock)
{
    for(auto player : mPlayers)
    {
        if(player->mSocket == sock)
            return player->mId;
    }
    return -1;
}



