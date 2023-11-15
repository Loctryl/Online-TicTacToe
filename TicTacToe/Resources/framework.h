#pragma once

#define REL_PTR(ptr) if(ptr) { delete (ptr); (ptr) = nullptr; }

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