#include "../Headers/GameManager.h"
#include <iostream>

GameManager::GameManager() {
   mainWindow = new SFMLWindow();
   mainGrid = new Grid();

   pieceSelected = nullptr;
   playerTurn = 0;
   forceEat = false;
}

GameManager::~GameManager() {
   //delete mainWindow;
}

void GameManager::InitGame() {
   mainWindow->InitWindow();
   const int tileSize = mainWindow->getVideoMode()->height / 12;
   const int marginLeft = mainWindow->getVideoMode()->width / 2 - tileSize * 5;
   mainGrid->InitGrid(tileSize, marginLeft);
}

void GameManager::RunGame() {
   Event event{};
   RenderGame();
   while (mainWindow->getWindow()->isOpen()){
      while (mainWindow->getWindow()->pollEvent(event)) {
         if (event.type == Event::Closed || event.key.code == Keyboard::Escape) mainWindow->getWindow()->close();
         if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            OnClick();
         }
      }
      RenderGame();
   }
}

void GameManager::OnClick() {
   if (mainGrid->IsMouseInGrid(Mouse::getPosition())) {
      Tile* tile = mainGrid->GetTile(Mouse::getPosition());

      if(!pieceSelected) {
         if(mainGrid->IsClickOnPiece(playerTurn, tile)){
            pieceSelected = tile;
            mainGrid->ClearHighlights();
            mainGrid->ShowFirstPossibilities(playerTurn, tile);
         }
      }
      else {
         if(mainGrid->IsClickOnHighLight(tile)) {
            bool eat = mainGrid->MovePiece(pieceSelected, tile);
            mainGrid->ClearHighlights();
            
            if(eat && mainGrid->ShowNextPossibilities(playerTurn, tile)) {
               pieceSelected = tile;
               forceEat = true;
            }
            else {
               pieceSelected = nullptr;
               playerTurn = !playerTurn;
               forceEat = false;
            }
         }
         else if(!forceEat) {
            mainGrid->ClearHighlights();
            pieceSelected = nullptr;

            if(mainGrid->IsClickOnPiece(playerTurn, tile)) {
               pieceSelected = tile;
               mainGrid->ClearHighlights();
               mainGrid->ShowFirstPossibilities(playerTurn, tile);
            }
         }
      }
      if(mainGrid->nbPieces[0] == 0 || mainGrid->nbPieces[1] == 0) {
         std::cout << "Game over" << std::endl;
         mainWindow->getWindow()->close();
      }
   }
}

void GameManager::DrawPlayerTurn() {
   Text text;

   // select the font
   text.setFont(mainWindow->getFont()); // font is a sf::Font

   // set the string to display
   text.setString("Player turn : ");

   // set the character size
   text.setCharacterSize(30); // in pixels, not points!

   // set the color
   text.setFillColor(Color::White);
   
   text.setStyle(Text::Bold);

   text.setPosition(99,99);
   
   //mainWindow->getWindow()->draw(text);
}


void GameManager::RenderGame() {
   mainWindow->getWindow()->clear();
   
   mainGrid->DrawGrid(mainWindow);

   DrawPlayerTurn();
   
   mainWindow->getWindow()->display();
}
