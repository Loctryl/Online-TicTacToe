#include "Headers/ClientRequestManager.h"
#include "Headers/ClientNetWork.h"
#include "Grid/Grid.h"

ClientRequestManager* ClientRequestManager::mInstance = nullptr;

ClientRequestManager::ClientRequestManager()
{
    mNetWork = new ClientNetWork();
    mGrid = new Grid();
}

ClientRequestManager::~ClientRequestManager()
{
    REL_PTR(mNetWork)
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

void ClientRequestManager::Play(int x, int y)
{
    mMyChoice[0] = x;
    mMyChoice[1] = y;

    SendRequestPlay(mMyChoice, ((ClientNetWork*)mNetWork)->GetClientSocket());
}

bool ClientRequestManager::Init()
{
    return ((ClientNetWork*)mNetWork)->Init();
}

bool ClientRequestManager::ManageMessage(std::string Message)
{
    json parsedMessage = json::parse(Message);
    std::string MessageType = parsedMessage["type"];

    switch (EventToInt(MessageType))
    {
    case play:
        // Le client recoit le coup de l'autre joueur
        mGrid->Play(parsedMessage["x"], parsedMessage["y"]);
        mGrid->mTurnPlayer = (mGrid->mTurnPlayer + 1) % 2;
        mIsMyTurn = true;
        break;

    case validation:
        // Le client recoit la réponse du serveur concernant son coup
        if (parsedMessage["answer"])// Si le coup est valide
            {
            mGrid->Play(mMyChoice[0], mMyChoice[1]);
            mGrid->mTurnPlayer = (mGrid->mTurnPlayer + 1) % 2;
            mIsMyTurn = false;
            }
        break;
    case winner:
        mGrid->mTurnPlayer = (mGrid->mTurnPlayer + 1) % 2;
        mIsMyTurn = false;
        mGrid->IsWinner();
        break;
    default:
        break;
    }

    return true;
}