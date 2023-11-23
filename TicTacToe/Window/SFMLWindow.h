#pragma once
#include "Utility\Resources\SfmlIncluder.h"
using namespace sf;


class SFMLWindow
{
private:
    RenderWindow* mWindow;
    VideoMode mVMode;
    Font mFont;

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
