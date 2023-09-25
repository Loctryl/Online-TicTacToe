#pragma once
#include "Structures.h"

struct Tile {
    int player, x, y;
    TILESTATE state;

    Tile() {
        player = 0;
        x = 0;
        y = 0;
        state = EMPTY;
    }

    Tile(int nplayer, int nx, int ny, TILESTATE nstate) {
        player = nplayer;
        x = nx;
        y = ny;
        state = nstate;
    }
};
