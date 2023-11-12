#include "GameManager.h"


int main() {
   GameManager* game = GameManager::GetInstance();

   game->InitGame();
   game->RunGame();
   return 0;
   
}
