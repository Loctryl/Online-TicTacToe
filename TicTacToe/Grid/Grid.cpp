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

bool Grid::TestChoice(int x, int y) const
{
    return mMainGrid[x][y] == -1;
}

void Grid::Play(int x, int y)
{
    mMainGrid[x][y] = mTurnPlayer;
    mTurnPlayer = (mTurnPlayer + 1) % 2;
}