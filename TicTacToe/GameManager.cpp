#include "GameManager.h"
#include "Grid/Grid.h"
#include "Window/SFMLWindow.h"

GameManager::GameManager()
{
    mWindow = new SFMLWindow();
    mGrid = new Grid();
}

GameManager::~GameManager()
{
    REL_PTR(mWindow)
    REL_PTR(mGrid)
}

void GameManager::InitGame(int gridSize)
{
    mWindow->InitWindow();
    mTileSize = mWindow->GetVideoMode()->height / (gridSize + 2);
    mMarginLeft = ((float)mWindow->GetVideoMode()->width / 2.f) - ((float)mTileSize * ((float)gridSize / 2.f));
    mGrid->InitGrid(gridSize);
}

void GameManager::Play(int x, int y, void (*func)()) const
{
    mGrid->mMainGrid[x][y] = 1;
    if(func)
        func();
}

bool GameManager::IsMove(int* x, int* y) const
{
    const Vector2i mousePos = Mouse::getPosition();
    if(mousePos.x >= mMarginLeft
        && mousePos.x <= mMarginLeft + mTileSize * mGrid->GetGridSize()
        && mousePos.y >= mTileSize
        && mousePos.y <= mTileSize * (mGrid->GetGridSize() + 1)
        )
    {
        *x = (mousePos.x - mMarginLeft) / mTileSize;
        *y = (mousePos.y - mTileSize) / mTileSize;
        return true;
    }
    return false;
}


void GameManager::RenderGame() const
{
    auto* rect = new RectangleShape();
    auto* circ = new CircleShape();

    const int gridSize = mGrid->GetGridSize();
    
    for (int x = 0; x< gridSize; x++)
    {
        for (int y = 0; y< gridSize; y++)
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

            if(mGrid->mMainGrid[x][y] != -1)
            {
                if(mGrid->mMainGrid[x][y] == 0)
                    circ->setFillColor(Color(240, 245, 185,255));
                else if(mGrid->mMainGrid[x][y] == 1)
                    circ->setFillColor(Color(145, 50, 1,255));
                
                circ->setRadius(mTileSize/2.5);
                circ->setPosition({
                   static_cast<float>(x * mTileSize + mMarginLeft + (mTileSize/10)),
                   static_cast<float>(y * mTileSize + mTileSize + (mTileSize/10))
                });
                
                mWindow->GetWindow()->draw(*circ);
            }
        }
    }
    REL_PTR(rect)
    REL_PTR(circ)
    mWindow->GetWindow()->display();
}

