#pragma once
#include "Window/SFMLWindow.h"

class Grid;
class SFMLWindow;

class GameManager
{
    Event* mEvent;

public:
    SFMLWindow* mWindow;
    Grid* mGrid;

    int mTileSize;
    float mMarginLeft;
    
    GameManager();
    ~GameManager();

    void InitWindow() const;

    void InitGrid(Grid* grid, int gridSize);

    bool IsWindowOpened() const;

    bool IsPressEsc(const Event* e) const;

    bool IsMouseClick(const Event* e) const;

    bool IsMove(int* x, int* y) const;
    
    void RenderGame() const;
    
    inline Event* GetEvent() { return mEvent; }
};