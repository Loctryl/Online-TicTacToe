#include "../Headers/SFMLWindow.h"

SFMLWindow::SFMLWindow() {
   _window = nullptr;
}

SFMLWindow::~SFMLWindow() {
   delete this->_window;
}

void SFMLWindow::InitWindow() {
   _v_mode = VideoMode::getDesktopMode();
   _window = new RenderWindow(
           _v_mode,
           "Classic Checkers",
           Style::Resize
   );
   _window->setPosition(Vector2i(0, 0));
   _window->setFramerateLimit(60);
   //if (!font.loadFromFile(FONT_ASSET_PATH)) throw("ERROR::FONT_LOADING");
}

RenderWindow* SFMLWindow::getWindow() { return _window; }
Font &SFMLWindow::getFont() { return _font; }
VideoMode* SFMLWindow::getVideoMode() { return &_v_mode; }