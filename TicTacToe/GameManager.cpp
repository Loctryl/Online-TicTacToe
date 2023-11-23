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
    mState = LOBBY;
}

GameManager::~GameManager()
{
    REL_PTR(mWindow)
    REL_PTR(mGrid)
}

void GameManager::InitWindow()
{
    mWindow->InitWindow();
    InitLobbyFields();
    
}

void GameManager::InitLobbyFields()
{
    float fieldHeight = mWindow->GetVideoMode()->height / 8.f;
    float fullWidthField = mWindow->GetVideoMode()->width / 1.5f;
    float alignLeft = mWindow->GetVideoMode()->width / 2.f - fullWidthField / 2;
    
    auto* rect = CreateRect({fullWidthField, fieldHeight},
                    {alignLeft, mWindow->GetVideoMode()->height / 4.f},
                    Color(150,150,150,255),
                    Color(130, 128, 126, 255),
                    2.f
        );
    mLobbyFields.push_back(rect);

    rect = CreateRect({fullWidthField - fullWidthField/5.f,fieldHeight},
                    {alignLeft,mWindow->GetVideoMode()->height / 2.f},
                    Color(150,150,150,255),
                    Color(130, 128, 126, 255),
                    2.f
        );
    mLobbyFields.push_back(rect);
    
    rect = CreateRect({fullWidthField/6.f, fieldHeight},
                    {alignLeft + fullWidthField - fullWidthField/6.f, mWindow->GetVideoMode()->height / 2.f},
                    Color(150,150,150,255),
                    Color(130, 128, 126, 255),
                    2.f
                    );
    mLobbyFields.push_back(rect);

    rect = CreateRect({mWindow->GetVideoMode()->width / 3.f, fieldHeight},
                        {mWindow->GetVideoMode()->width / 2.f - (mWindow->GetVideoMode()->width / 3.f) / 2, mWindow->GetVideoMode()->height / 1.2f},
                        Color(100,100,100,255),
                        Color(100,100,100,255),
                        0.f
    );
    mLobbyFields.push_back(rect);
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

int GameManager::ClickOnField() const
{
    const Vector2i mousePos = Mouse::getPosition();
    POINT pos = {mousePos.x, mousePos.y};
    ScreenToClient(mWindow->GetWindow()->getSystemHandle(), &pos);

    for(int i = 0; i < mLobbyFields.size(); i++)
        if(pos.x >= mLobbyFields[i]->getPosition().x
        &&pos.x <= mLobbyFields[i]->getPosition().x + mLobbyFields[i]->getSize().x
        &&pos.y >= mLobbyFields[i]->getPosition().y
        &&pos.y <= mLobbyFields[i]->getPosition().y + mLobbyFields[i]->getSize().y
        )
            return i;
    
    return -1;
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

RectangleShape* GameManager::CreateRect(Vector2f size, Vector2f pos, Color fillColor, Color outlineColor, float outlineThick)
{
    auto* rect = new RectangleShape();
    rect->setSize(size);
    rect->setPosition(pos);
    rect->setFillColor(fillColor);
    rect->setOutlineColor(outlineColor);
    rect->setOutlineThickness(outlineThick);
    return rect;
}

void GameManager::DrawTextW(std::string str, int size, Color color, Vector2f position, Vector2f offset)
{
    Text text;
    text.setFont(*mWindow->GetFont());
    text.setString(str);
    text.setCharacterSize(size); // in pixels, not points!
    text.setFillColor(color);

    text.setPosition({position.x + offset.x, position.y + offset.y});
    
    mWindow->GetWindow()->draw(text);
}


void GameManager::Render()
{
    switch (mState)
    {
        case LOBBY:
            RenderLobby();
            break;
        case IN_GAME:
        case GAME_OVER:    
            RenderGame();
            break;
    }
}

void GameManager::RenderLobby()
{
    mWindow->GetWindow()->clear(Color(249, 193, 130, 255));
    
    DrawTextW("TicTacToe", 70, Color::Red, {mWindow->GetVideoMode()->width / 2.f - 150.f, 20.f}, {0,0});

    mLobbyFields[mSelectedField]->setOutlineColor(Color::Cyan);
    mLobbyFields[!mSelectedField]->setOutlineColor(Color(130, 128, 126, 255));
    
    for(int i = 0; i < mLobbyFields.size(); i++)
    {
        mWindow->GetWindow()->draw(*mLobbyFields[i]);
        if(i < 2)
            DrawTextW(mInfo[i], 45, Color::Black, mLobbyFields[i]->getPosition(), {20.f,10.f});
        switch (i)
        {
            case 2:
                DrawTextW("Try", 45, Color::Black, mLobbyFields[i]->getPosition(), {10.f,5.f});
                break;
            case 3:
                DrawTextW("Play", 70, Color::Black, mLobbyFields[i]->getPosition(), {60.f,-10.f});
                break;
            default: break;
        }
    }

    mWindow->GetWindow()->display();
}

void GameManager::RenderGame()
{
    mWindow->GetWindow()->clear(Color(249, 193, 130, 255));
    
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
            rect->setOutlineThickness(2.f);
            rect->setOutlineColor(Color(130, 128, 126, 255));
            
            if (x%2==0 && y%2!=0 || x%2!=0 && y%2==0)
                rect->setFillColor(Color(156, 152, 147, 255));
            else
                rect->setFillColor(Color(206, 202, 197, 255));

            mWindow->GetWindow()->draw(*rect);

            if (mGrid->mMainGrid[x][y]!=-1)
            {
                if (mGrid->mMainGrid[x][y]==0)
                    circ->setFillColor(Color(173, 58, 35, 255));
                else if (mGrid->mMainGrid[x][y]==1)
                    circ->setFillColor(Color(35, 173, 139, 255));

                circ->setRadius(mTileSize/2.5);
                circ->setPosition({
                        static_cast<float>(x*mTileSize+mMarginLeft+(mTileSize/10)),
                        static_cast<float>(y*mTileSize+mTileSize+(mTileSize/10))
                    });

                mWindow->GetWindow()->draw(*circ);
            }
        }
    }

    if(mGrid->mWinner != -1 && mGrid->mWinner != -2)
    {
        DrawTextW("Game Over !", 15, Color::Red, {mWindow->GetVideoMode()->width / 2.f, 5.f }, {0,0});
        circ->setRadius(mTileSize/2.5);
    
        if (mGrid->mWinner==0)
        {
            circ->setPosition({50.f, 50.f});
            circ->setFillColor(Color(173, 58, 35, 255));
        }
        else if (mGrid->mWinner==1)
        {
            circ->setPosition({mWindow->GetVideoMode()->width - 100.f, 50.f});
            circ->setFillColor(Color(35, 173, 139, 255));
        }

        circ->setOutlineColor(Color(255, 20, 20, 255));
        circ->setOutlineThickness(2.f);
    
        mWindow->GetWindow()->draw(*circ);
    }
    
    REL_PTR(rect)
    REL_PTR(circ)

    mWindow->GetWindow()->display();
}