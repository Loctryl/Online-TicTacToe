#pragma once
#include <vector>
#include "Player.h"

class Grid
{
public:
    std::vector<std::vector<int>> mMainGrid;
    int mSize = 3;

    UINT mPlayers[2];
    int mTurnPlayer = 0;
    
    Grid(int gridSize = 3);
    ~Grid();
    
    void InitGrid(int gridSize);

    void Play(int x, int y);

    bool IsTileEmpty(int x, int y) const { return mMainGrid[x][y] == -1; }

    inline int GetGridSize() const { return mSize;}
    inline int GetValue(int x, int y) const { return mMainGrid[x][y]; }
};
