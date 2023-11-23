#include "SFMLWindow.h"

#include <iostream>

SFMLWindow::SFMLWindow() { mWindow = nullptr; }

SFMLWindow::~SFMLWindow() { delete this->mWindow; }

void SFMLWindow::InitWindow()
{
    mVMode = VideoMode::getDesktopMode();
    mVMode.width = 800;
    mVMode.height = 600;
    mWindow = new RenderWindow(
        mVMode,
        "Classic TICTACTOOOOOOOOOOOOEE",
        Style::Default
    );
    mWindow->setPosition(Vector2i(0, 0));
    mWindow->setFramerateLimit(60);
    // Issue on loading font
    //if (!mFont.loadFromFile("Resources\\Roboto-Regular.ttf")) std::cout << "not loaded" <<std::endl;
}

RenderWindow* SFMLWindow::GetWindow() const { return mWindow; }
Font* SFMLWindow::GetFont() { return &mFont; }
VideoMode* SFMLWindow::GetVideoMode() { return &mVMode; }
