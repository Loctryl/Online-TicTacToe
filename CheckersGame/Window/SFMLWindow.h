#pragma once
#include <SFML\Graphics.hpp>
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
   RenderWindow* GetWindow() const;

   /// Return the used font
   Font* GetFont();

   /// Returns the window's video mode
   VideoMode* GetVideoMode();

   /// Initiates the windows and its parameters
   void InitWindow();
};