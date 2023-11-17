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
    
    GameManager();
    ~GameManager();

    void InitGame(int gridSize = 3);

    void Play(int x, int y,void (*func)() = nullptr) const;

    bool IsWindowOpened() const;

    bool IsPressEsc(const Event* e) const;

    bool IsMouseClick(const Event* e) const;

    bool IsMove(int* x, int* y) const;
    
    void RenderGame() const;
};