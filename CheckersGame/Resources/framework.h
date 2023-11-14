#pragma once

#define REL_PTR(ptr) if(ptr) { delete (ptr); (ptr) = nullptr; }

// Sfml libs
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;

#include <string>
#include <iostream>
using namespace std;


const std::string FONT_ASSET_PATH = "Assets/arial.ttf";

enum TILE_STATE { EMPTY, SIMPLE, QUEEN, HIGHLIGHT };

constexpr int ALL_DIRECTIONS[4][2] = {{-1,-1},{1,1},{1,-1},{-1,1}};

constexpr int WHITE_FORWARDS[2][2] = {{-1,-1},{1,-1}};

constexpr int BLACK_FORWARDS[2][2] = {{1,1},{-1,1}};