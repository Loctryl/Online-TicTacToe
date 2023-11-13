#include "GameManager.h"
#include <iostream>
#include <WS2tcpip.h>

#include "Grid/Grid.h"
#include "Window/SFMLWindow.h"

GameManager* GameManager::mInstance = nullptr;

GameManager::GameManager() {
   mMainWindow = new SFMLWindow();
   mMainGrid = new Grid();

   mPieceSelected = nullptr;
   mPlayerTurn = 0;
   mForceEat = false;
   mCurrentState = IDLE;
}

GameManager* GameManager::GetInstance()
{
   if (mInstance != nullptr) return mInstance;
   mInstance = new GameManager();
   return mInstance;
}


void GameManager::InitGame() const {
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
   //POINT pos = {Mouse::getPosition().x, Mouse::getPosition().y};
   //ScreenToClient(mMainWindow->GetWindow()->getSystemHandle(), &pos);
   
   if (mMainGrid->IsMouseInGrid(Mouse::getPosition())) {
      Tile* tile = mMainGrid->GetTile(Mouse::getPosition());

      bool eat = false;
      
      switch (mCurrentState) {
         case IDLE:
            if(mMainGrid->IsClickOnPiece(mPlayerTurn, tile))
            {
               mPieceSelected = tile;
               mCurrentState = SELECTING;
               mMainGrid->ClearHighlights();
               mMainGrid->ShowFirstPossibilities(mPlayerTurn, tile);
            }
            break;
         
         case SELECTING:
            if(mMainGrid->IsClickOnHighLight(tile))
            {
               eat = mMainGrid->MovePiece(mPieceSelected, tile);
               mMainGrid->ClearHighlights();
               mCurrentState = PLAYING;
            }
            else if(!mForceEat)
            {
               mMainGrid->ClearHighlights();
               mPieceSelected = nullptr;
               mCurrentState = IDLE;
            }
            break;
         
         case PLAYING:
            if(eat && mMainGrid->ShowNextPossibilities(mPlayerTurn, tile))
            {
               mPieceSelected = tile;
               mForceEat = true;
               mCurrentState = SELECTING;
            }
            else
            {
               mPieceSelected = nullptr;
               mPlayerTurn = !mPlayerTurn;
               mForceEat = false;
               mCurrentState = IDLE;
            }
            break;
      }
      std::cout << mCurrentState << std::endl;

      if(mMainGrid->nbPieces[0] == 0 || mMainGrid->nbPieces[1] == 0)
      {
         std::cout << "Game over" << std::endl;
         mMainWindow->GetWindow()->close();
      }
   }
}

void GameManager::DrawPlayerTurn() const {
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


void GameManager::RenderGame() const {
   mMainWindow->GetWindow()->clear();
   
   mMainGrid->DrawGrid(mMainWindow);

   DrawPlayerTurn();
   
   mMainWindow->GetWindow()->display();
}
