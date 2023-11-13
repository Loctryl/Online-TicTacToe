#include "SFMLWindow.h"
#include "SFML/Graphics.hpp"
using namespace sf;

SFMLWindow::SFMLWindow() {
   _window = nullptr;
}

SFMLWindow::~SFMLWindow() {
   delete this->_window;
}

void SFMLWindow::InitWindow() {
   _v_mode = VideoMode::getDesktopMode();
   _v_mode.width = 1280;
   _v_mode.height = 720;
   _window = new RenderWindow(
           _v_mode,
           "Classic Checkers",
           Style::Default
   );
   _window->setPosition(Vector2i(0, 0));
   _window->setFramerateLimit(60);
   // Issue on loading font
   //if (!_font.loadFromFile(FONT_ASSET_PATH)) throw;
}

RenderWindow* SFMLWindow::GetWindow() const { return _window; }
Font* SFMLWindow::GetFont() { return &_font; }
VideoMode* SFMLWindow::GetVideoMode() { return &_v_mode; }