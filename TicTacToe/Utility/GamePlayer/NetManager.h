#pragma once
#include <vector>
#include <winsock2.h>

class Grid;
class Player;

class NetManager
{
public:
    NetManager();
    ~NetManager();

    Grid* mWaitingGame;

    std::vector<Grid*> mGames;
    std::vector<Player*> mPlayers;

    void CreateGame();

    void AddGame(Grid* game);
    void AddPlayer();

    Grid* GetGameByPlayerId(int id) const;
    int GetPlayerBySocket(SOCKET sock);
};