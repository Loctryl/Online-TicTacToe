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
}

int Grid::IsWinner() 
{
    int countDown;

    for (int j = 0; j < mSize; j++) {
        countDown = 0;
        for (int i = 0; i < mSize; i++) {
            if (mMainGrid[j][i] != mTurnPlayer)
                break;
            countDown++;
        }
        if (countDown == mSize)
            mWinner = mTurnPlayer;   
    }

    for (int j = 0; j < mSize; j++) {
        countDown = 0;
        for (int i = 0; i < mSize; i++) {
            if (mMainGrid[i][j] != mTurnPlayer)
                break;
            countDown++;
        }
        if (countDown == mSize)
            mWinner = mTurnPlayer;   
    }

    countDown = 0;
    for (int i = 0; i < mSize; i++) {
        if (mMainGrid[i][i] != mTurnPlayer)
            break;
        countDown++;
    }
    if (countDown == mSize)
        mWinner = mTurnPlayer;

    countDown = 0;
    for (int i = mSize-1; i > 0 ; i--) {
        if (mMainGrid[i][i] != mTurnPlayer)
            break;
        countDown++;
    }
    if (countDown == mSize)
        mWinner = mTurnPlayer;

    return mWinner;
}