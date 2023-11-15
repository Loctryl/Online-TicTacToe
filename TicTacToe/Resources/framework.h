#pragma once

#define REL_PTR(ptr) if(ptr) { delete (ptr); (ptr) = nullptr; }

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;

#include <string>
#include <iostream>
using namespace std;

enum TILE_STATE { EMPTY, CROSS, ROUND };