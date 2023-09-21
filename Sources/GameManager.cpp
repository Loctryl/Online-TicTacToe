#include "../Headers/GameManager.h"

GameManager::GameManager() {
   mainWindow = new SFMLWindow();
   //player = new Player();
}

GameManager::~GameManager() {
   //delete mainWindow;
}

void GameManager::InitGame() const {
   mainWindow->InitWindow();
   //player->Init(mainWindow->getWindow(), {0,0});
}

void GameManager::RunGame() const {
   Event event{};
   Clock deltaClock;
   while (mainWindow->getWindow()->isOpen()){
      Time time = deltaClock.restart();
      const float deltaTime = time.asSeconds();
      while (mainWindow->getWindow()->pollEvent(event))
      {
         if (event.type == Event::Closed || event.key.code == Keyboard::Escape) mainWindow->getWindow()->close();
         if(event.type == Event::KeyPressed){
            KeyEvent(event.key.code);
         }
      }
      UpdateGame(deltaTime);
      RenderGame();
   }
}

void GameManager::KeyEvent(Keyboard::Key keyPressed) const {
   
}
void GameManager::UpdateGame(float deltaTime) const {
   //player->Update(deltaTime);
}

void GameManager::RenderGame() const {
   DrawGrid();
   //player->Render();
   mainWindow->getWindow()->display();
}

void GameManager::DrawGrid() const {
   for(int x = 0; x < mainWindow->getVideoMode()->width / TILE_SIZE ; x++)
      for (int y = 0; y < mainWindow->getVideoMode()->height / TILE_SIZE; y ++) {
         auto* _rect = new RectangleShape();
         _rect->setSize({static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE)});
         _rect->setPosition({static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE)});
         _rect->setOutlineThickness(1);
         _rect->setOutlineColor(Color(12,80,138,255));
         if (x % 2 == 0 && y % 2 != 0 || x % 2 != 0 && y % 2 == 0)
            _rect->setFillColor(Color(50, 50, 50, 255));
         else
            _rect->setFillColor(Color(30, 30, 30, 255));
         mainWindow->getWindow()->draw(*_rect);
      }
}
