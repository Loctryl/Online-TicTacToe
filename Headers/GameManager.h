#pragma once
#include "SFMLWindow.h"
#include <iostream>

#include "Grid.h"

class GameManager {
   int playerTurn;
   Tile* pieceSelected;
   
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

   void UpdateGame() const;

   void RenderGame() const;
};
