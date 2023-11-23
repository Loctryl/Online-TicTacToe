#include "GameManager.h"
#include "RequestManager.h"

#include <Grid/Player.h>

#include "NetWork.h"
#include "Utility/Resources/utilities.h"
#include "Utility/Thread/Thread.h"
#include "Grid/Grid.h"

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

void ClientRequestManager::JoinGame(string nickname) const
{
    SendRequestJoin(((ClientNetWork*)mNetWork)->GetClientSocket(), nickname, 0);
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
        if(!mGame->mGrid)
        {
            mGame->InitGrid(nullptr);
            mGame->mState = IN_GAME;
        }
        mGame->mGrid->mPlayers[parsedMessage["player"]] = new Player();
        mGame->mGrid->mPlayers[parsedMessage["player"]]->mNickName = parsedMessage["nickname"];
        mIsMyTurn = true;
        break;

    case leave:
        REL_PTR(mGame->mGrid)
        mGame->mState = LOBBY;
        break;
    default:
        break;
    }

    return true;
}