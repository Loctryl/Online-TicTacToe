#pragma once
#include "SFMLWindow.h"

#include "Grid.h"

class GameManager {
   int playerTurn;
   Tile* pieceSelected;
   bool forceEat;
   
public:
   static GameManager& getInstance() {
      static GameManager instance;
      return instance;
   }
   
   GameManager();
   ~GameManager();

   SFMLWindow* mainWindow;

   Grid* mainGrid;

   void InitGame();

   void RunGame();

   void OnClick();

   void DrawPlayerTurn();

   void RenderGame();
};
