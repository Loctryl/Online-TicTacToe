#pragma once
#include <Window/SFMLWindow.h>

#include <iostream>

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

    inline bool IsWindowOpened() const { return mWindow->GetWindow()->isOpen(); }

    inline bool IsPressEsc(const Event* e) const { return (e->type == Event::Closed || e->key.code == Keyboard::Escape); }

    inline bool IsMouseClick(const Event* e) const { return (e->type == Event::MouseButtonPressed && e->mouseButton.button == Mouse::Left); }

    bool IsMove(int* x, int* y) const;
    
    void RenderGame() const;
};
