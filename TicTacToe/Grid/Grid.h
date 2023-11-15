#pragma once
#include <vector>

class SFMLWindow;

class Grid
{
public:
    std::vector<std::vector<int>> mMainGrid;
    int mSize = 3;
    
    Grid();

    ~Grid();
    
    void InitGrid(int gridSize);

    void Play();

    inline int GetGridSize() const { return mSize;}
    inline int GetValue(int x, int y) const { return mMainGrid[x][y]; }
};
