#pragma once
#include "Tile.h"
#include "SFMLWindow.h"

class Grid {
public:
    Tile* mainGrid[10][10];

    int tileSize;
    int marginLeft;

    Grid();
    ~Grid();

    void InitGrid(int, int);

    bool IsMouseInGrid(Vector2i);

    bool IsClickOnPiece(int, Tile*);

    bool IsClickOnHighLight(Tile*);

    Tile* GetTile(Vector2i);

    void ShowPossibilities(Tile*);

    void MovePiece(Tile*, Tile*);

    void DrawGrid(SFMLWindow*);

    void ClearHighlights();
};
