#pragma once
#include "Resources/framework.h"

struct Tile {
    int player, x, y;
    TILE_STATE state;

    Tile() {
        player = 0;
        x = 0;
        y = 0;
        state = EMPTY;
    }

    Tile(int nPlayer, int nx, int ny, TILE_STATE nState) {
        player = nPlayer;
        x = nx;
        y = ny;
        state = nState;
    }
};
