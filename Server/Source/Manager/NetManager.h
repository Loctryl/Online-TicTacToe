#pragma once
#include <string>
#include <vector>
#include "Resources/framework.h"

class Grid;
class Player;

class NetManager
{
public:
    NetManager();
    ~NetManager();

    static NetManager* GetInstance();

    Grid* CreateGame();
    void DeleteGame(int gameId);
    void CreatePlayer(SOCKET* sock, std::string name = "");
    void SetPlayerNickname(SOCKET* sock, std::string name) const;

    void AddPlayerToGame(Player* p);

    Grid* GetGameByPlayerId(int id) const;
    Player* GetPlayerBySocket(SOCKET* sock) const;
    Player* GetPlayerById(int id) const;

    Player* GetEnemyPlayer(SOCKET* sock);
    Player* GetEnemyPlayer(int id) const;

    std::vector<Grid*> GetGames();

    int SetNewPlayerID();
    int SetNewGameID();

private:
    static NetManager* mInstance;

    Grid* mWaitingGame;

    std::vector<Grid*> mGames;
    std::vector<Player*> mPlayers;

    int mPlayerMaxId = 0;
    int mGameMaxId = 0;
};