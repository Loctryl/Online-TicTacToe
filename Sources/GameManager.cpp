#include "../Headers/GameManager.h"

GameManager::GameManager() {
   mainWindow = new SFMLWindow();
   //player = new Player();
}

GameManager::~GameManager() {
   //delete mainWindow;
}

void GameManager::InitGame() {
   int count = 0;
   mainWindow->InitWindow();
   //player->Init(mainWindow->getWindow(), {0,0});

   tileSize = mainWindow->getVideoMode()->height / 12;
   margin = mainWindow->getVideoMode()->width / 2 - tileSize * 5;

   for(int y = 0; y<10;y++) {
      for(int x = 0; x<10;x++) {
         if (x % 2 == 0 && y % 2 != 0 || x % 2 != 0 && y % 2 == 0) {
            if (count <= 40) {
               Piece* npiece = new Piece(2,x,y,SIMPLE);
               mainGrid[x][y] = npiece;
            } else if (count >= 60) {
               Piece* npiece = new Piece(1,x,y,SIMPLE);
               mainGrid[x][y] = npiece;
            } else
               mainGrid[x][y] = nullptr;
         } else
            mainGrid[x][y] = nullptr;
         count++;
      }
   }
}

void GameManager::RunGame() const {
   Event event{};
   
   while (mainWindow->getWindow()->isOpen()){
      while (mainWindow->getWindow()->pollEvent(event))
      {
         if (event.type == Event::Closed || event.key.code == Keyboard::Escape) mainWindow->getWindow()->close();
         if(event.type == Event::KeyPressed){
            KeyEvent(event.key.code);
         }
         UpdateGame();
         RenderGame();
      }
   }
}

void GameManager::KeyEvent(Keyboard::Key keyPressed) const {
   
}
void GameManager::UpdateGame() const {
   
}

void GameManager::RenderGame() const {
   DrawGrid();
   
   mainWindow->getWindow()->display();
}

void GameManager::DrawGrid() const {
   for(int x = 0; x < 10 ; x++) {
      for (int y = 0; y < 10; y ++) {
         auto* _rect = new RectangleShape();
         auto* _circ = new CircleShape();
         
         _rect->setSize({static_cast<float>(tileSize), static_cast<float>(tileSize)});
         _rect->setPosition({
            static_cast<float>(x * tileSize + margin),
            static_cast<float>(y * tileSize + tileSize)
         });
         _rect->setOutlineThickness(1);
         _rect->setOutlineColor(Color(12,80,138,255));
         if (x % 2 == 0 && y % 2 != 0 || x % 2 != 0 && y % 2 == 0)
            _rect->setFillColor(Color(20, 20, 20, 255));
         else
            _rect->setFillColor(Color(70, 70, 70, 255));

         
         if (mainGrid[x][y] != nullptr) {
            if (mainGrid[x][y]->player == 1) 
               _circ->setFillColor(Color(240, 245, 185,255));
            else
               _circ->setFillColor(Color(145, 50, 1,255));

            if (mainGrid[x][y]->state == QUEEN) {
               _circ->setOutlineColor(Color(255,0,0));
               _circ->setOutlineThickness(2);
            }
            
            _circ->setRadius(tileSize/2.5);
            _circ->setPosition({
               static_cast<float>(x * tileSize + margin + (tileSize/10)),
               static_cast<float>(y * tileSize + tileSize + (tileSize/10))
            });
            mainWindow->getWindow()->draw(*_circ);
         }
         mainWindow->getWindow()->draw(*_rect);
      }
   }
}
