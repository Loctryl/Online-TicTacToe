#pragma once
#include <string>

const std::string FONT_ASSET_PATH = "Assets/arial.ttf";

enum TILESTATE { EMPTY, SIMPLE, QUEEN, HIGHLIGHT };

const int all_directions[4][2] = {{-1,-1},{1,1},{1,-1},{-1,1}};

const int white_forwards[2][2] = {{-1,-1},{1,-1}};

const int black_forwards[2][2] = {{1,1},{-1,1}};
