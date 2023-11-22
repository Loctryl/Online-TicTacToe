#include <Resources/utilities.h>
#include <Window/SFMLWindow.h>
#include "Grid/Grid.h"
#include "GameManager.h"

#include <iostream>
#include <Utility/RequestManager/RequestManager.h>

#include "Windows.h"

GameManager::GameManager()
{
    mEvent = new Event();
    mWindow = new SFMLWindow();
    mGrid = nullptr;
    mTileSize = 0;
    mMarginLeft = 0;
}

GameManager::~GameManager()
{
    REL_PTR(mWindow)
    REL_PTR(mGrid)
}

void GameManager::InitWindow() const
{
    mWindow->InitWindow();
}

void GameManager::InitGrid(Grid* grid)
{
    if (grid)
        mGrid = grid;
    else
        mGrid = new Grid();

    mTileSize = mWindow->GetVideoMode()->height/(mGrid->mSize+2);
    mMarginLeft = ((float)mWindow->GetVideoMode()->width/2.f)-((float)mTileSize*((float)mGrid->mSize/2.f));
}

bool GameManager::IsWindowOpened() const { return mWindow->GetWindow()->isOpen(); }

bool GameManager::IsPressEsc(const Event* e) const { return (e->type==Event::Closed /*|| e->key.code==Keyboard::Escape*/); }

bool GameManager::IsMouseClick(const Event* e) const
{
    return (e->type==Event::MouseButtonPressed&&e->mouseButton.button==Mouse::Left);
}

bool GameManager::IsMove(int* x, int* y) const
{
    const Vector2i mousePos = Mouse::getPosition();
    POINT pos = {mousePos.x, mousePos.y};
    ScreenToClient(mWindow->GetWindow()->getSystemHandle(), &pos);

    if (pos.x>=mMarginLeft
        &&pos.x<=mMarginLeft+mTileSize*mGrid->GetGridSize()
        &&pos.y>=mTileSize
        &&pos.y<=mTileSize*(mGrid->GetGridSize()+1)
    )
    {
        *x = (pos.x-mMarginLeft)/mTileSize;
        *y = (pos.y-mTileSize)/mTileSize;
        if (mGrid->mMainGrid[*x][*y]==-1)
            return true;
    }
    return false;
}

void GameManager::Render() const
{
    switch (mState)
    {
        case LOBBY:
            RenderLobby();
            break;
        
        case IN_GAME:
            if(mGrid)
                RenderGame();
            break;
        case GAME_OVER:    
            RenderGame();
            break;
    }
}


void GameManager::RenderLobby() const
{
    mWindow->GetWindow()->clear();
    
    auto* rect = new RectangleShape();

    rect->setPosition(mWindow->GetVideoMode()->width / 2, mWindow->GetVideoMode()->height / 2);
    rect->setSize({100,100});
    rect->setFillColor(Color(200,200,200,255));
    mWindow->GetWindow()->draw(*rect);

    mWindow->GetWindow()->display();
}

void GameManager::RenderGame() const
{
    mWindow->GetWindow()->clear();
    
    auto* rect = new RectangleShape();
    auto* circ = new CircleShape();

    const int gridSize = mGrid->GetGridSize();

    for (int x = 0; x<gridSize; x++)
    {
        for (int y = 0; y<gridSize; y++)
        {
            rect->setSize({static_cast<float>(mTileSize), static_cast<float>(mTileSize)});
            rect->setPosition({
                    static_cast<float>(x*mTileSize+mMarginLeft),
                    static_cast<float>(y*mTileSize+mTileSize)
                });
            rect->setOutlineThickness(1);
            rect->setOutlineColor(Color(12, 80, 138, 255));
            
            if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0)
                rect->setFillColor(Color(20, 20, 20, 255));
            else
                rect->setFillColor(Color(70, 70, 70, 255));

            mWindow->GetWindow()->draw(*rect);

            if (mGrid->mMainGrid[x][y]!=-1)
            {
                if (mGrid->mMainGrid[x][y]==0)
                    circ->setFillColor(Color(240, 245, 185, 255));
                else if (mGrid->mMainGrid[x][y]==1)
                    circ->setFillColor(Color(145, 50, 1, 255));

                circ->setRadius(mTileSize/2.5);
                circ->setPosition({
                        static_cast<float>(x*mTileSize+mMarginLeft+(mTileSize/10)),
                        static_cast<float>(y*mTileSize+mTileSize+(mTileSize/10))
                    });

                mWindow->GetWindow()->draw(*circ);
            }
        }
    }

    if(mGrid->mWinner != -1)
    {
        circ->setRadius(mTileSize/2.5);
        circ->setPosition({50.f, 50.f});
    
        if (mGrid->mWinner==0)
            circ->setFillColor(Color(240, 245, 185, 255));
        else if (mGrid->mWinner==1)
            circ->setFillColor(Color(145, 50, 1, 255));

        circ->setOutlineColor(Color(255, 20, 20, 255));
        circ->setOutlineThickness(2.f);
    
        mWindow->GetWindow()->draw(*circ);
    }

    REL_PTR(rect)
    REL_PTR(circ)

    mWindow->GetWindow()->display();
}