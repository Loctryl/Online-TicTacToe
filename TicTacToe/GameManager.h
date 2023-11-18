#pragma once
#include "Window/SFMLWindow.h"

class Grid;
class SFMLWindow;

class GameManager
{
public:
    SFMLWindow* mWindow;
    Grid* mGrid;

    int mTileSize;
    float mMarginLeft;
    
    GameManager(Grid* grid = nullptr, int gridSize = 3);
    ~GameManager();

    void InitWindow();

    bool TestChoice(int x, int y) const;
    void Play(int x, int y) const;

    bool IsWindowOpened() const;

    bool IsPressEsc(const Event* e) const;

    bool IsMouseClick(const Event* e) const;

    bool IsMove(int* x, int* y) const;
    
    void RenderGame() const;
};