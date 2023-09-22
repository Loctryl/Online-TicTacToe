#pragma once
#include "SFMLWindow.h"
#include <iostream>
#include "Piece.h"

class GameManager {
private:
   int tileSize;
   int margin;
   int playerTurn;
   
public:
   static GameManager& getInstance() {
      static GameManager instance;
      return instance;
   }
   GameManager();
   ~GameManager();

   SFMLWindow* mainWindow;

   Piece* mainGrid[10][10];

   //Player* player;

   void InitGame();

   void RunGame() const;

   void KeyEvent(Keyboard::Key) const;

   void UpdateGame() const;

   void RenderGame() const;

   void DrawGrid() const;
};
