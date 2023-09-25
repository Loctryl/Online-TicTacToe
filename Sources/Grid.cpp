#include "../Headers/Grid.h"
#include <iostream>
#include <stdlib.h>

Grid::Grid() {
    
}

Grid::~Grid() { }

void Grid::InitGrid(int size, int margin) {
    tileSize = size;
    marginLeft = margin;
    
    int count = 0;
    for(int y = 0; y<10;y++) {
        for(int x = 0; x<10;x++) {
            if (x % 2 == 0 && y % 2 != 0 || x % 2 != 0 && y % 2 == 0) {
                if (count <= 40) {
                    mainGrid[x][y] = Tile(1,x,y,SIMPLE);
                } else if (count >= 60) {
                    mainGrid[x][y] = Tile(0,x,y,SIMPLE);
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

bool Grid::IsMouseInGrid(Vector2i mousePos) {
    if(mousePos.x >= marginLeft
        and mousePos.x <= marginLeft+tileSize*10
        and mousePos.y >= tileSize
        and mousePos.y <= tileSize*11
        )
        return true;
    return false;
}

bool Grid::IsClickOnPiece(int player, Tile* tile) {
    if ((mainGrid[tile->x][tile->y].state == SIMPLE
        or mainGrid[tile->x][tile->y].state == QUEEN)
        and mainGrid[tile->x][tile->y].player == player)
        return true;
    return false;
}

bool Grid::IsClickOnHighLight(Tile* tile) {
    if (mainGrid[tile->x][tile->y].state == HIGHLIGHT) return true;
    return false;
}


Tile* Grid::GetTile(Vector2i mousePos) {
    int x = (mousePos.x - marginLeft) / tileSize;
    int y = (mousePos.y - tileSize) / tileSize;
    return &mainGrid[x][y];
}

bool Grid::IsPlayableTile(int dir, Tile* tile, int player) {
    if(mainGrid[tile->x + all_directions[dir][0]][tile->y + all_directions[dir][1]].state == EMPTY
        and dir % 2 == player % 2) return true;
    return false;
}

bool Grid::IsEatableTile(int dir, Tile* tile, int player) {
    if((mainGrid[tile->x + all_directions[dir][0]][tile->y + all_directions[dir][1]].state == SIMPLE
        or mainGrid[tile->x + all_directions[dir][0]][tile->y + all_directions[dir][1]].state == QUEEN)
        and mainGrid[tile->x + all_directions[dir][0]][tile->y + all_directions[dir][1]].player != player
        and mainGrid[tile->x + all_directions[dir][0]*2][tile->y + all_directions[dir][1]*2].state == EMPTY) return true;
    return false;
}

void Grid::ShowFirstPossibilities(int player, Tile* tile) { 
    if(tile->state == SIMPLE) {
        for (int dir = 0; dir < 4; dir ++) {
            if(IsPlayableTile(dir, tile, player)) 
                ShowHighLight({tile->x + all_directions[dir][0],tile->y + all_directions[dir][1]}, player);
            
            if(IsEatableTile(dir, tile, player)) {
                ShowHighLight({tile->x + all_directions[dir][0]*2,tile->y + all_directions[dir][1]*2}, player);
            }
        }
    } else if (tile->state == QUEEN) {
        for (int dir = 0; dir < 4; dir ++) {
            int n = 1;
            //std::cout << "en boucle ?" << std::endl;
            /*while(&mainGrid[tile->x + all_directions[dir][0]*n][tile->y + all_directions[dir][0]*n] != nullptr) {
                if(IsPlayableTile(dir, tile, player)) {
                    ShowHighLight({tile->x + all_directions[dir][0],tile->y + all_directions[dir][1]}, player);
                    std::cout << "oui ?" << std::endl;
                }
            
                if(IsEatableTile(dir, tile, player)) {
                    ShowHighLight({tile->x + all_directions[dir][0]*2,tile->y + all_directions[dir][1]*2}, player);
                }
                n++;
            }*/
        }
    }
}

bool Grid::ShowNextPossibilities(int player, Tile* tile) {
    bool ret = false;
    
    if(tile->state == SIMPLE) {
        for (int dir = 0; dir < 4; dir ++) {
            if(IsEatableTile(dir, tile, player)) {
                ShowHighLight({tile->x + all_directions[dir][0]*2,tile->y + all_directions[dir][1]*2}, player);
                ret = true;
            }
        }
    }
    return ret;
}

void Grid::ShowHighLight(Vector2i coord, int playnum) {
    if(coord.x >= 0 and coord.x <= 10 and coord.y >= 0 and coord.y <= 10) {
        mainGrid[coord.x][coord.y].state = HIGHLIGHT;
        mainGrid[coord.x][coord.y].player = playnum;
    }
}

bool Grid::MovePiece(Tile* selected, Tile* hl) {
    hl->player = selected->player;
    hl->state = selected->state;
    selected->player = -1;
    selected->state = EMPTY;

    if((hl->y == 0 and hl->player == 0) or (hl->y == 9 and hl->player == 1)) hl->state = QUEEN;

    if(abs(hl->x - selected->x)>=2) {
        Vector2i dir = {selected->x - hl->x < 0 ? 1 : -1, selected->y - hl->y < 0 ? 1 : -1};
        for (int i = 1; i < abs(hl->x - selected->x); i++) {
            mainGrid[selected->x + dir.x*i][selected->y + dir.y*i].state = EMPTY;
            mainGrid[selected->x + dir.x*i][selected->y + dir.y*i].player = -1;
        }
        return true;
    }
    return false;
}

void Grid::SetPieceColor(CircleShape* _circ, Vector2i xy) {
    if (mainGrid[xy.x][xy.y].player == 0) 
        _circ->setFillColor(Color(240, 245, 185,255));
    else
        _circ->setFillColor(Color(145, 50, 1,255));
}

void Grid::DrawGrid(SFMLWindow* mainWindow) {
    for(int x = 0; x < 10 ; x++) {
        for (int y = 0; y < 10; y ++) {
            auto* _rect = new RectangleShape();
            auto* _circ = new CircleShape();
         
            _rect->setSize({static_cast<float>(tileSize), static_cast<float>(tileSize)});
            _rect->setPosition({
               static_cast<float>(x * tileSize + marginLeft),
               static_cast<float>(y * tileSize + tileSize)
            });
            _rect->setOutlineThickness(1);
            _rect->setOutlineColor(Color(12,80,138,255));
            if (x % 2 == 0 && y % 2 != 0 || x % 2 != 0 && y % 2 == 0)
                _rect->setFillColor(Color(20, 20, 20, 255));
            else
                _rect->setFillColor(Color(70, 70, 70, 255));

            mainWindow->getWindow()->draw(*_rect);
         
            if (mainGrid[x][y].state != EMPTY) {
                switch (mainGrid[x][y].state) {
                case SIMPLE:
                    SetPieceColor(_circ, {x,y});
                    break;
                case QUEEN:
                    SetPieceColor(_circ, {x,y});
                    _circ->setOutlineColor(Color(255,0,0));
                    _circ->setOutlineThickness(2);
                    break;
                case HIGHLIGHT:
                    if (mainGrid[x][y].player == 0) 
                        _circ->setFillColor(Color(240, 245, 185,150));
                    else
                        _circ->setFillColor(Color(145, 50, 1,150));
                    break;
                case EMPTY: break;
                }
            
                _circ->setRadius(tileSize/2.5);
                _circ->setPosition({
                   static_cast<float>(x * tileSize + marginLeft + (tileSize/10)),
                   static_cast<float>(y * tileSize + tileSize + (tileSize/10))
                });
                
                mainWindow->getWindow()->draw(*_circ);
            }
        }
    }
}

void Grid::ClearHighlights() {
    for(int x = 0;x < 10;x++) {
        for (int y = 0; y< 10;y++) {
            if(mainGrid[x][y].state == HIGHLIGHT) {
                mainGrid[x][y].state = EMPTY;
                mainGrid[x][y].player = -1;
            }
        }
    }
}

