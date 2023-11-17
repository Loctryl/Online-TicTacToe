#include "Grid.h"

Grid::Grid() { }

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

void Grid::Play() {}
