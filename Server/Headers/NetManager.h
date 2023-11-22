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
    Player* GetPlayerBySocket(SOCKET* sock) const;
    Player* GetPlayerById(int id) const;

    Player* GetEnemyPlayer(SOCKET* sock);
    Player* GetEnemyPlayer(int id);

    std::vector<Grid*> GetGames();

    int SetNewID();

private:
    static NetManager* mInstance;

    Grid* mWaitingGame;

    std::vector<Grid*> mGames;
    std::vector<Player*> mPlayers;

    int mCurrentId = 0;
};