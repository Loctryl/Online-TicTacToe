#include "../Headers/Grid.h"

#include <iostream>

Grid::Grid() { }

Grid::~Grid() { }

void Grid::InitGrid(int size, int margin) {
    tileSize = size;
    marginLeft = margin;
    
    int count = 0;
    for(int y = 0; y<10;y++) {
        for(int x = 0; x<10;x++) {
            if (x % 2 == 0 && y % 2 != 0 || x % 2 != 0 && y % 2 == 0) {
                if (count <= 40) {
                    Tile* ntile = new Tile(2,x,y,SIMPLE);
                    mainGrid[x][y] = ntile;
                } else if (count >= 60) {
                    Tile* ntile = new Tile(1,x,y,SIMPLE);
                    mainGrid[x][y] = ntile;
                } else {
                    Tile* ntile = new Tile(0,x,y,EMPTY);
                    mainGrid[x][y] = ntile;
                }
            } else {
                Tile* ntile = new Tile(0,x,y,EMPTY);
                mainGrid[x][y] = ntile;
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
    if ((mainGrid[tile->x][tile->y]->state == SIMPLE
        or mainGrid[tile->x][tile->y]->state == QUEEN)
        and mainGrid[tile->x][tile->y]->player == player)
        return true;
    return false;
}

bool Grid::IsClickOnHighLight(Tile* tile) {
    if (mainGrid[tile->x][tile->y]->state == HIGHLIGHT) return true;
    return false;
}


Tile* Grid::GetTile(Vector2i mousePos) {
    int x = (mousePos.x - marginLeft) / tileSize;
    int y = (mousePos.y - tileSize) / tileSize;
    return mainGrid[x][y];
}

void Grid::ShowPossibilities(Tile* tile) { 
    if(tile->state == SIMPLE) {
        mainGrid[tile->x - 1][tile->y - 1]->state = HIGHLIGHT;
        mainGrid[tile->x - 1][tile->y - 1]->player = tile->player;
    } 
}

void Grid::MovePiece(Tile* selected, Tile* hl) {
    hl->player = selected->player;
    hl->state = selected->state;
    selected->player = 0;
    selected->state = EMPTY;
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
         
            if (mainGrid[x][y]->state != EMPTY) {
                switch (mainGrid[x][y]->state) {
                case SIMPLE:
                    if (mainGrid[x][y]->player == 1) 
                        _circ->setFillColor(Color(240, 245, 185,255));
                    else
                        _circ->setFillColor(Color(145, 50, 1,255));
                    break;
                case QUEEN:
                    _circ->setOutlineColor(Color(255,0,0));
                    _circ->setOutlineThickness(2);
                    break;
                case HIGHLIGHT:
                    if (mainGrid[x][y]->player == 1) 
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
            if(mainGrid[x][y]->state == HIGHLIGHT) {
                mainGrid[x][y]->state = EMPTY;
                mainGrid[x][y]->player = 0;
            }
        }
    }
}

