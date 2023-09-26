#pragma once
#include "Tile.h"
#include "SFMLWindow.h"

class Grid {
public:
    Tile mainGrid[10][10];

    int tileSize;
    int marginLeft;

    Grid();
    ~Grid();

    void InitGrid(int, int);

    bool IsMouseInGrid(Vector2i);

    bool IsClickOnPiece(int, Tile*);

    bool IsClickOnHighLight(Tile*);

    Tile* GetTile(Vector2i);

    bool IsPlayableTile(int, Tile*, int);

    bool IsQueenPlayableTile(int, Tile*, int, int);
    
    bool IsEatableTile(int, Tile*, int, int);

    void ShowHighLight(Vector2i, int);

    void ShowFirstPossibilities(int, Tile*);

    bool ShowNextPossibilities(int, Tile*);

    bool MovePiece(Tile*, Tile*);

    void SetPieceColor(CircleShape*, Vector2i);

    void DrawGrid(SFMLWindow*);

    void ClearHighlights();
};
