#include "SFML/Graphics.hpp"
#include "Headers/GameManager.h"
using namespace std;


int main() {
   GameManager game = GameManager::getInstance();

   game.InitGame();
   game.RunGame();
   return 0;
   
}
