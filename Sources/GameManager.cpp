#include "../Headers/GameManager.h"

GameManager::GameManager() {
   mainWindow = new SFMLWindow();
   mainGrid = new Grid();

   playerTurn = 1;
}

GameManager::~GameManager() {
   //delete mainWindow;
}

void GameManager::InitGame() {
   mainWindow->InitWindow();
   int tileSize = mainWindow->getVideoMode()->height / 12;
   int marginLeft = mainWindow->getVideoMode()->width / 2 - tileSize * 5;
   mainGrid->InitGrid(tileSize, marginLeft);
}

void GameManager::RunGame() {
   Event event{};
   RenderGame();
   while (mainWindow->getWindow()->isOpen()){
      while (mainWindow->getWindow()->pollEvent(event)) {
         if (event.type == Event::Closed || event.key.code == Keyboard::Escape) mainWindow->getWindow()->close();
         if(event.type == Event::MouseButtonPressed and event.mouseButton.button == Mouse::Left) {
            OnClick();
         }
      }
   }
}

void GameManager::OnClick() {
   if (mainGrid->IsMouseInGrid(Mouse::getPosition())) {
      Tile* tile = mainGrid->GetTile(Mouse::getPosition());

      if(!pieceSelected) {
         if(mainGrid->IsClickOnPiece(playerTurn, tile)){
            pieceSelected = tile;
            mainGrid->ClearHighlights();
            mainGrid->ShowPossibilities(tile);
         }
      }
      if (mainGrid->IsClickOnHighLight(tile)) {
         mainGrid->MovePiece(pieceSelected, tile);
         mainGrid->ClearHighlights();
         pieceSelected = nullptr;
      }
   }

   
   RenderGame();
}

void GameManager::RenderGame() const {
   mainWindow->getWindow()->clear();
   
   mainGrid->DrawGrid(mainWindow);
   
   mainWindow->getWindow()->display();
}
