#pragma once
#include "Tile.h"
#include "SFMLWindow.h"

class Grid {
public:
    Tile mainGrid[10][10];

    int tileSize;
    int marginLeft;
    int nbPieces[2];

    Grid();
    ~Grid();

    void InitGrid(int, int);

    bool IsMouseInGrid(Vector2i) const;

    bool IsClickOnPiece(int, Tile*) const;

    bool IsClickOnHighLight(Tile*) const;

    Tile* GetTile(Vector2i);

    bool IsPlayableTile(int, Tile*, int) const;

    bool IsQueenPlayableTile(int, Tile*, int, int) const;
    
    bool IsEatableTile(int, Tile*, int, int) const;

    void ShowHighLight(Vector2i, int);

    void ShowFirstPossibilities(int, Tile*);

    bool ShowNextPossibilities(int, Tile*);

    bool MovePiece(Tile*, Tile*);

    void SetPieceColor(CircleShape*, Vector2i) const;

    void DrawGrid(SFMLWindow*);

    void ClearHighlights();

    bool IsEnd();
};
