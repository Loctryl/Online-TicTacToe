#include "Grid.h"

Grid::Grid(int gridSize)
{
    InitGrid(gridSize);
}

Grid::~Grid() { }

void Grid::InitGrid(int gridSize)
{
    mSize = gridSize;

    for (int x = 0; x<mSize; x++)
    {
        mMainGrid.emplace_back();
        for (int y = 0; y<mSize; y++)
            mMainGrid[x].push_back(-1);
    }
}

bool Grid::Play(int x, int y)
{
    if (mMainGrid[x][y] == -1)
    {
        mMainGrid[x][y] = mTurnPlayer;
        mTurnPlayer = (mTurnPlayer + 1) % 2;
        return true;
    }
    else
        return false;
}