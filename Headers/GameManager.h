#pragma once
#include "SFMLWindow.h"

class GameManager {
public:
   static GameManager& getInstance() {
      static GameManager instance;
      return instance;
   }
   GameManager();
   ~GameManager();

   SFMLWindow* mainWindow;

   //Player* player;

   void InitGame() const;

   void RunGame() const;

   void KeyEvent(Keyboard::Key) const;

   void UpdateGame(float) const;

   void RenderGame() const;

   void DrawGrid() const;
};
