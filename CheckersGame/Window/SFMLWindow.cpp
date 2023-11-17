#include "SFMLWindow.h"
#include "SFML/Graphics.hpp"
using namespace sf;

SFMLWindow::SFMLWindow() {
   mWindow = nullptr;
}

SFMLWindow::~SFMLWindow() {
   delete this->mWindow;
}

void SFMLWindow::InitWindow() {
   mVMode = VideoMode::getDesktopMode();
   mVMode.width = 1280;
   mVMode.height = 720;
   mWindow = new RenderWindow(
           mVMode,
           "Classic Checkers",
           Style::Default
   );
   mWindow->setPosition(Vector2i(0, 0));
   mWindow->setFramerateLimit(60);
   // Issue on loading font
   //if (!_font.loadFromFile(FONT_ASSET_PATH)) throw;
}

RenderWindow* SFMLWindow::GetWindow() const { return mWindow; }
Font* SFMLWindow::GetFont() { return &mFont; }
VideoMode* SFMLWindow::GetVideoMode() { return &mVMode; }