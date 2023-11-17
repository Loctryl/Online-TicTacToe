#pragma once
#include <string>
#include <winsock2.h>

class Grid;

struct Player
{
    UINT mId;
    UINT mInGameId;
    std::string mNickName;
    SOCKET* mSocket;
    Grid* mCurrentGame;
};
