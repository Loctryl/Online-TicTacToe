#pragma once
#include "Window/SFMLWindow.h"

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

    std::vector<RectangleShape* > mLobbyFields;

public:
    SFMLWindow* mWindow;
    Grid* mGrid;
    GAME_STATE mState;

    std::string mInfo[2];
    int mSelectedField = 0;

    int mTileSize;
    float mMarginLeft;
    
    GameManager();
    ~GameManager();

    void InitWindow();

    void InitLobbyFields();

    void InitGrid(Grid* grid);

    bool IsWindowOpened() const;

    bool IsPressEsc(const Event* e) const;

    bool IsMouseClick(const Event* e) const;

    int ClickOnField() const;

    bool IsMove(int* x, int* y) const;

    RectangleShape* CreateRect(Vector2f size, Vector2f pos, Color fillColor, Color outlineColor, float outlineThick);

    void DrawTextW(std::string str, int size, Color color, Vector2f position, Vector2f offset);

    void Render();

    void RenderLobby();
    
    void RenderGame();
    
    inline Event* GetEvent() const { return mEvent; }
};