#include "GameManager.h"
#include "Headers/ClientRequestManager.h"
#include "Headers/ClientNetWork.h"
#include "Grid/Grid.h"
#include "Resources/utilities.h"
#include "Utility/Thread/Thread.h"

ClientRequestManager* ClientRequestManager::mInstance = nullptr;

ClientRequestManager::ClientRequestManager()
{
    mNetWork = new ClientNetWork();
    mGame = nullptr;
}

ClientRequestManager::~ClientRequestManager()
{
    REL_PTR(mNetWork)
    mGame = nullptr;
}

ClientRequestManager* ClientRequestManager::GetInstance()
{
    if (mInstance != nullptr) return mInstance;
    mInstance = new ClientRequestManager();
    return mInstance;
}

bool ClientRequestManager::IsMyTurn() const
{
    return mIsMyTurn;
}

void ClientRequestManager::JoinGame() const
{
    SendRequestJoin(((ClientNetWork*)mNetWork)->GetClientSocket());
}

void ClientRequestManager::Play(int x, int y)
{
    mMyChoice[0] = x;
    mMyChoice[1] = y;

    SendRequestPlay(mMyChoice, ((ClientNetWork*)mNetWork)->GetClientSocket());
}

void ClientRequestManager::LeaveGame() const
{
    SendRequestLeave(((ClientNetWork*)mNetWork)->GetClientSocket());
}


bool ClientRequestManager::Init(ThreadObj* thread)
{
    return ((ClientNetWork*)mNetWork)->Init(thread);
}

bool ClientRequestManager::ManageMessage(std::string Message)
{
    json parsedMessage = json::parse(Message);
    std::string MessageType = parsedMessage["type"];

    switch (EventToInt(MessageType))
    {
    case play:
        // Le client recoit le coup de l'autre joueur
        mGame->mGrid->Play(parsedMessage["x"], parsedMessage["y"]);
        mGame->mGrid->mTurnPlayer = (mGame->mGrid->mTurnPlayer + 1) % 2;
        mIsMyTurn = true;
        break;

    case validation:
        // Le client recoit la réponse du serveur concernant son coup
        if (parsedMessage["answer"])// Si le coup est valide
            {
            mGame->mGrid->Play(mMyChoice[0], mMyChoice[1]);
            mGame->mGrid->mTurnPlayer = (mGame->mGrid->mTurnPlayer + 1) % 2;
            mIsMyTurn = false;
            }
        break;
        
    case winner:
        mGame->mGrid->mTurnPlayer = (mGame->mGrid->mTurnPlayer + 1) % 2;
        mIsMyTurn = false;
        mGame->mGrid->IsWinner();
        mGame->mState = GAME_OVER;
        break;

    case join:
        mGame->InitGrid(nullptr);
        mGame->mState = IN_GAME;
        mIsMyTurn = true;
        break;

    case leave:
        mGame->mGrid = nullptr;
        mGame->mState = LOBBY;
        break;
    default:
        break;
    }

    return true;
}