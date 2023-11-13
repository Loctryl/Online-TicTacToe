#include "GameManager.h"
#include <iostream>
#include "Grid/Grid.h"
#include "Window/SFMLWindow.h"

GameManager* GameManager::mInstance = nullptr;

GameManager::GameManager() {
   mMainWindow = new SFMLWindow();
   mMainGrid = new Grid();

   mPieceSelected = nullptr;
   mPlayerTurn = 0;
   mForceEat = false;
}

GameManager::~GameManager() {
   //delete mainWindow;
}

GameManager* GameManager::GetInstance()
{
   if (mInstance != nullptr) return mInstance;
   mInstance = new GameManager();
   return mInstance;
}


void GameManager::InitGame() {
   mMainWindow->InitWindow();
   const int tileSize = mMainWindow->GetVideoMode()->height / 12;
   const int marginLeft = mMainWindow->GetVideoMode()->width / 2 - tileSize * 5;
   mMainGrid->InitGrid(tileSize, marginLeft);
}

void GameManager::RunGame() {
   Event event{};
   RenderGame();
   while (mMainWindow->GetWindow()->isOpen()){
      while (mMainWindow->GetWindow()->pollEvent(event)) {
         if (event.type == Event::Closed || event.key.code == Keyboard::Escape) mMainWindow->GetWindow()->close();
         if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            OnClick();
         }
      }
      RenderGame();
   }
}

void GameManager::OnClick() {
   if (mMainGrid->IsMouseInGrid(Mouse::getPosition())) {
      Tile* tile = mMainGrid->GetTile(Mouse::getPosition());

      if(!mPieceSelected) {
         if(mMainGrid->IsClickOnPiece(mPlayerTurn, tile)){
            mPieceSelected = tile;
            mMainGrid->ClearHighlights();
            mMainGrid->ShowFirstPossibilities(mPlayerTurn, tile);
         }
      }
      else {
         if(mMainGrid->IsClickOnHighLight(tile)) {
            bool eat = mMainGrid->MovePiece(mPieceSelected, tile);
            mMainGrid->ClearHighlights();
            
            if(eat && mMainGrid->ShowNextPossibilities(mPlayerTurn, tile)) {
               mPieceSelected = tile;
               mForceEat = true;
            }
            else {
               mPieceSelected = nullptr;
               mPlayerTurn = !mPlayerTurn;
               mForceEat = false;
            }
         }
         else if(!mForceEat) {
            mMainGrid->ClearHighlights();
            mPieceSelected = nullptr;

            if(mMainGrid->IsClickOnPiece(mPlayerTurn, tile)) {
               mPieceSelected = tile;
               mMainGrid->ClearHighlights();
               mMainGrid->ShowFirstPossibilities(mPlayerTurn, tile);
            }
         }
      }
      if(mMainGrid->nbPieces[0] == 0 || mMainGrid->nbPieces[1] == 0) {
         std::cout << "Game over" << std::endl;
         mMainWindow->GetWindow()->close();
      }
   }
}

void GameManager::DrawPlayerTurn() {
   Text text;

   // select the font
   text.setFont(*mMainWindow->GetFont()); // font is a sf::Font

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
   mMainWindow->GetWindow()->clear();
   
   mMainGrid->DrawGrid(mMainWindow);

   DrawPlayerTurn();
   
   mMainWindow->GetWindow()->display();
}
