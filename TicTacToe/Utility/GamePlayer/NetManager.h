#pragma once
#include <vector>
#include <string>
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

    Grid* CreateGame();
    void CreatePlayer(SOCKET* sock, std::string name);

    void AddPlayerToGame(Player* p);

    Grid* GetGameByPlayerId(int id) const;
    int GetPlayerBySocket(SOCKET* sock) const;
};