#pragma once

class SFMLWindow;
class Grid;
struct Tile;


class GameManager
{
    int mPlayerTurn;
    bool mForceEat;
    
    SFMLWindow* mMainWindow;
    Grid* mMainGrid;
    Tile* mPieceSelected;
    

public:
    static GameManager* mInstance;
    
    static GameManager* GetInstance();

    GameManager();
    ~GameManager();

    void InitGame();

    void RunGame();

    void OnClick();

    void DrawPlayerTurn();

    void RenderGame();
};
