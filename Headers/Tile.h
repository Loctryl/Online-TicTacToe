#pragma once
#include "Structures.h"

struct Tile {
    int player, x, y;
    TILESTATE state;

    Tile(int nplayer, int nx, int ny, TILESTATE nstate) {
        player = nplayer;
        x = nx;
        y = ny;
        state = nstate;
    }
};
