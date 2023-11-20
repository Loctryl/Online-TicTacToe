#pragma once
#include "framework.h"
#include <vector>
#include <string>

class Grid;
class Player;

class NetManager
{
public:
    NetManager();
    ~NetManager();

    static NetManager* GetInstance();

    Grid* CreateGame();
    void CreatePlayer(SOCKET* sock, std::string name = "");
    void SetPlayerNickname(SOCKET* sock, std::string name);

    void AddPlayerToGame(Player* p);

    Grid* GetGameByPlayerId(int id) const;
    int GetPlayerBySocket(SOCKET* sock) const;

private:
    static NetManager* mInstance;

    Grid* mWaitingGame;

    std::vector<Grid*> mGames;
    std::vector<Player*> mPlayers;
};