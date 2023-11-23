#pragma once
#include "Utility/RequestManager/RequestManager.h"
#include "NetWork.h"

class GameManager;
class ThreadObj;

struct Choice
{
    int x, y;
};

class ClientRequestManager : public RequestManager
{
public:
    ~ClientRequestManager() override;

    static ClientRequestManager* GetInstance();
    bool Init(ThreadObj* thread) override;

    bool IsMyTurn() const;

    void Play(int x, int y);

    void JoinGame(string nickname) const;

    void LeaveGame() const;
    
    bool ManageMessage(std::string Message);

    inline ClientNetWork* GetNetWork() const { return (ClientNetWork*)mNetWork; }

    int mMyChoice[2] = {};
    GameManager* mGame;

private:
    static ClientRequestManager* mInstance;

    bool mIsMyTurn = false;

    ClientRequestManager();
};
