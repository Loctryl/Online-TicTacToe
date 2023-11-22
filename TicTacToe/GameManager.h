#pragma once
#include "Window/SFMLWindow.h"

class RequestManager;
class StateMachine;
class Grid;
class SFMLWindow;

enum GAME_STATE
{
    LOBBY,
    IN_GAME,
    GAME_OVER
};

class GameManager
{
    Event* mEvent;

public:
    SFMLWindow* mWindow;
    Grid* mGrid;
    GAME_STATE mState;

    int mTileSize;
    float mMarginLeft;
    
    GameManager();
    ~GameManager();

    void InitWindow() const;

    void InitGrid(Grid* grid);

    bool IsWindowOpened() const;

    bool IsPressEsc(const Event* e) const;

    bool IsMouseClick(const Event* e) const;

    bool IsMove(int* x, int* y) const;

    void Render() const;

    void RenderLobby() const;
    
    void RenderGame() const;
    
    inline Event* GetEvent() const { return mEvent; }
};