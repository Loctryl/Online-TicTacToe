#include "Headers/ClientRequestManager.h"
#include "Headers/ClientNetWork.h"

ClientRequestManager* ClientRequestManager::mInstance = nullptr;

ClientRequestManager::ClientRequestManager() { mNetWork = new ClientNetWork(); }

ClientRequestManager::~ClientRequestManager()
{
    delete mNetWork;
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

void ClientRequestManager::Play(int coord[2])
{
    mMyChoice[0] = coord[0];
    mMyChoice[1] = coord[1];

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
    case play:// Le client recoit le coup de l'autre joueur
        //game.Play(parsedMessage["x"], parsedMessage["y"])
        // MAJ EndGame
        mIsMyTurn = true;
        break;

    case validation:// Le client recoit la réponse du serveur concernant son coup
        if (parsedMessage["answer"])// Si le coup est valide
        {
            //game.Play(mMyChoice[0], mMyChoice[1])
            // MAJ EndGame
            mIsMyTurn = false;
        }
        break;

    default:
        break;
    }

    return true;
}