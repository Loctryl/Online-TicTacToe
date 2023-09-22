#pragma once
#include "Structures.h"

struct Piece {
    int player, x, y;
    PIECESTATE state;

    Piece(int nplayer, int nx, int ny, PIECESTATE nstate) {
        player = nplayer;
        x = nx;
        y = ny;
        state = nstate;
    }
};
