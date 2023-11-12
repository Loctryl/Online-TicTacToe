#pragma once
#include <string>

#define REL_PTR(ptr) if(ptr) { delete (ptr); (ptr) = nullptr; }

const std::string FONT_ASSET_PATH = "Assets/arial.ttf";

enum TILE_STATE { EMPTY, SIMPLE, QUEEN, HIGHLIGHT };

constexpr int ALL_DIRECTIONS[4][2] = {{-1,-1},{1,1},{1,-1},{-1,1}};

constexpr int WHITE_FORWARDS[2][2] = {{-1,-1},{1,-1}};

constexpr int BLACK_FORWARDS[2][2] = {{1,1},{-1,1}};
