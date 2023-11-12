#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class SFMLWindow {
private:
   RenderWindow* _window;
   VideoMode _v_mode;
   Font _font;
   
public:
   SFMLWindow();
   ~SFMLWindow();

   /// Returns the window
   RenderWindow* getWindow();

   /// Return the used font
   Font &getFont();

   /// Returns the window's video mode
   VideoMode* getVideoMode();

   /// Initiates the windows and its parameters
   void InitWindow();
};
