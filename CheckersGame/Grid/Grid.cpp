#include "Grid.h"
#include "Tile.h"
#include <iostream>

Grid::Grid() {
    tileSize = 0;
    marginLeft = 0;
    nbPieces[0] = 0;
    nbPieces[1] = 0;
}

void Grid::InitGrid(int size, int margin) {
    tileSize = size;
    marginLeft = margin;
    
    int count = 0;
    for(int y = 0; y<10;y++) {
        for(int x = 0; x<10;x++) {
            if (x % 2 == 0 && y % 2 != 0 || x % 2 != 0 && y % 2 == 0) {
                if (count <= 40) {
                    mainGrid[x][y] = Tile(1,x,y,SIMPLE);
                    nbPieces[1]++;
                } else if (count >= 60) {
                    mainGrid[x][y] = Tile(0,x,y,SIMPLE);
                    nbPieces[0]++;
                } else {
                    mainGrid[x][y] = Tile(-1,x,y,EMPTY);
                }
            } else {
                mainGrid[x][y] =  Tile(-1,x,y,EMPTY);
            }
            count++;
        }
    }
}

bool Grid::IsMouseInGrid(Vector2i mousePos) const {
    if(mousePos.x >= marginLeft
        && mousePos.x <= marginLeft+tileSize*10
        && mousePos.y >= tileSize
        && mousePos.y <= tileSize*11
        )
        return true;
    return false;
}

bool Grid::IsClickOnPiece(int player, Tile* tile) const {
    if ((mainGrid[tile->x][tile->y].state == SIMPLE
        || mainGrid[tile->x][tile->y].state == QUEEN)
        && mainGrid[tile->x][tile->y].player == player)
        return true;
    return false;
}

bool Grid::IsClickOnHighLight(Tile* tile) const  {
    if (mainGrid[tile->x][tile->y].state == HIGHLIGHT) return true;
    return false;
}


Tile* Grid::GetTile(Vector2i mousePos) {
    int x = (mousePos.x - marginLeft) / tileSize;
    int y = (mousePos.y - tileSize) / tileSize;
    return &mainGrid[x][y];
}

bool Grid::IsPlayableTile(int dir, Tile* tile, int player) const {
    if(dir % 2 == player % 2
        && mainGrid[tile->x + ALL_DIRECTIONS[dir][0]][tile->y + ALL_DIRECTIONS[dir][1]].state == EMPTY) return true;
    return false;
}

bool Grid::IsQueenPlayableTile(int dir, Tile* tile, int player, int n) const {
    if(mainGrid[tile->x + ALL_DIRECTIONS[dir][0]*n][tile->y + ALL_DIRECTIONS[dir][1]*n].state == EMPTY) return true;
    return false;
}

bool Grid::IsEatableTile(int dir, Tile* tile, int player, int n) const {
    if((mainGrid[tile->x + ALL_DIRECTIONS[dir][0]*n][tile->y + ALL_DIRECTIONS[dir][1]*n].state == SIMPLE
        || mainGrid[tile->x + ALL_DIRECTIONS[dir][0]*n][tile->y + ALL_DIRECTIONS[dir][1]*n].state == QUEEN)
        && mainGrid[tile->x + ALL_DIRECTIONS[dir][0]*n][tile->y + ALL_DIRECTIONS[dir][1]*n].player != player
        && mainGrid[tile->x + ALL_DIRECTIONS[dir][0]*(n+1)][tile->y + ALL_DIRECTIONS[dir][1]*(n+1)].state == EMPTY) return true;
    return false;
}

void Grid::ShowFirstPossibilities(int player, Tile* tile) { 
    if(tile->state == SIMPLE) {
        for (int dir = 0; dir < 4; dir ++) {
            if(IsPlayableTile(dir, tile, player)) 
                ShowHighLight({tile->x + ALL_DIRECTIONS[dir][0],tile->y + ALL_DIRECTIONS[dir][1]}, player);
            
            if(IsEatableTile(dir, tile, player, 1)) 
                ShowHighLight({tile->x + ALL_DIRECTIONS[dir][0]*2,tile->y + ALL_DIRECTIONS[dir][1]*2}, player);
        }
    }
    else if (tile->state == QUEEN) {
        for (int dir = 0; dir < 4; dir ++) {
            int n = 1;
            bool eat = false;
            
            while(tile->x + ALL_DIRECTIONS[dir][0]*n >= 0
                && tile->x + ALL_DIRECTIONS[dir][0]*n < 10
                && tile->y + ALL_DIRECTIONS[dir][1]*n >= 0
                && tile->y + ALL_DIRECTIONS[dir][1]*n < 10) {
                if(IsQueenPlayableTile(dir, tile, player, n)) {
                    ShowHighLight({tile->x + ALL_DIRECTIONS[dir][0]*n,tile->y + ALL_DIRECTIONS[dir][1]*n}, player);
                }
                else if(!IsEatableTile(dir, tile, player, n) || eat) break;
                else eat = true;
                
                n++;
            }
        }
    }
}

bool Grid::ShowNextPossibilities(int player, Tile* tile) {
    bool ret = false;
    
    if(tile->state == SIMPLE) {
        for (int dir = 0; dir < 4; dir ++) {
            if(IsEatableTile(dir, tile, player, 1)) {
                ShowHighLight({tile->x + ALL_DIRECTIONS[dir][0]*2,tile->y + ALL_DIRECTIONS[dir][1]*2}, player);
                ret = true;
            }
        }
    }
    else if(tile->state == QUEEN) {
        for (int dir = 0; dir < 4; dir ++) {
            int n = 1;
            bool eat = false;

            while(tile->x + ALL_DIRECTIONS[dir][0]*n >= 0
                && tile->x + ALL_DIRECTIONS[dir][0]*n < 10
                && tile->y + ALL_DIRECTIONS[dir][1]*n >= 0
                && tile->y + ALL_DIRECTIONS[dir][1]*n < 10) {
                
                if(IsEatableTile(dir, tile, player, n)) eat = true;
                if(eat && IsQueenPlayableTile(dir, tile, player, n)) {
                    if(!IsEatableTile(dir, tile, player, n)) {
                        ShowHighLight({tile->x + ALL_DIRECTIONS[dir][0]*n,tile->y + ALL_DIRECTIONS[dir][1]*n}, player);
                        ret = true;
                    } else break;
                }

                n++;
            }   
        }
    }
    return ret;
}

void Grid::ShowHighLight(Vector2i coord, int playnum) {
    if(coord.x >= 0 && coord.x < 10 && coord.y >= 0 && coord.y < 10) {
        mainGrid[coord.x][coord.y].state = HIGHLIGHT;
        mainGrid[coord.x][coord.y].player = playnum;
    }
}

bool Grid::MovePiece(Tile* selected, Tile* hl) {
    hl->player = selected->player;
    hl->state = selected->state;
    selected->player = -1;
    selected->state = EMPTY;

    bool eating = false;

    if((hl->y == 0 && hl->player == 0) || (hl->y == 9 && hl->player == 1)) hl->state = QUEEN;

    if(abs(hl->x - selected->x)>=2) {
        Vector2i dir = {selected->x - hl->x < 0 ? 1 : -1, selected->y - hl->y < 0 ? 1 : -1};
        for (int i = 1; i < abs(hl->x - selected->x); i++) {
            if(mainGrid[selected->x + dir.x*i][selected->y + dir.y*i].state == SIMPLE || mainGrid[selected->x + dir.x*i][selected->y + dir.y*i].state == QUEEN) {
                eating = true;
                nbPieces[mainGrid[selected->x + dir.x*i][selected->y + dir.y*i].player]--;
            }
            mainGrid[selected->x + dir.x*i][selected->y + dir.y*i].state = EMPTY;
            mainGrid[selected->x + dir.x*i][selected->y + dir.y*i].player = -1;
        }
    }
    return eating;
}

void Grid::SetPieceColor(CircleShape* _circ, Vector2i xy) const {
    if (mainGrid[xy.x][xy.y].player == 0) 
        _circ->setFillColor(Color(240, 245, 185,255));
    else
        _circ->setFillColor(Color(145, 50, 1,255));
}

void Grid::DrawGrid(SFMLWindow* mainWindow) const {
    auto* rect = new RectangleShape();
    auto* circ = new CircleShape();
    for(int x = 0; x < 10 ; x++) {
        for (int y = 0; y < 10; y ++) {
         
            rect->setSize({static_cast<float>(tileSize), static_cast<float>(tileSize)});
            rect->setPosition({
               static_cast<float>(x * tileSize + marginLeft),
               static_cast<float>(y * tileSize + tileSize)
            });
            rect->setOutlineThickness(1);
            rect->setOutlineColor(Color(12,80,138,255));
            if (x % 2 == 0 && y % 2 != 0 || x % 2 != 0 && y % 2 == 0)
                rect->setFillColor(Color(20, 20, 20, 255));
            else
                rect->setFillColor(Color(70, 70, 70, 255));

            mainWindow->GetWindow()->draw(*rect);
         
            if (mainGrid[x][y].state != EMPTY) {
                switch (mainGrid[x][y].state) {
                case SIMPLE:
                    SetPieceColor(circ, {x,y});
                    break;
                case QUEEN:
                    SetPieceColor(circ, {x,y});
                    circ->setOutlineColor(Color(255,0,0));
                    circ->setOutlineThickness(2);
                    break;
                case HIGHLIGHT:
                    if (mainGrid[x][y].player == 0) 
                        circ->setFillColor(Color(240, 245, 185,150));
                    else
                        circ->setFillColor(Color(145, 50, 1,150));
                    break;
                case EMPTY: break;
                }
            
                circ->setRadius(tileSize/2.5);
                circ->setPosition({
                   static_cast<float>(x * tileSize + marginLeft + (tileSize/10)),
                   static_cast<float>(y * tileSize + tileSize + (tileSize/10))
                });
                
                mainWindow->GetWindow()->draw(*circ);
            }
        }
    }
    REL_PTR(rect);
    REL_PTR(circ);
}

void Grid::ClearHighlights() {
    for(int x = 0;x < 10;x++)
        for (int y = 0; y< 10;y++) 
            if(mainGrid[x][y].state == HIGHLIGHT) {
                mainGrid[x][y].state = EMPTY;
                mainGrid[x][y].player = -1;
            }
}

