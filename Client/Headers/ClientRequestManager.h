#pragma once
#include "Utility/RequestManager/RequestManager.h"
#include "ClientNetWork.h"

class Grid;

class ClientRequestManager : public RequestManager
{
public:
    ~ClientRequestManager() override;

    static ClientRequestManager* GetInstance();
    bool Init() override;

    bool IsMyTurn() const;

    void Play(int coord[2]);

    void JoinGame() const;

    void LeaveGame() const;
    
    bool ManageMessage(std::string Message);

    inline ClientNetWork* GetNetWork() const { return (ClientNetWork*)mNetWork; }

    int mMyChoice[2] = {};
    Grid* mGrid;

private:
    static ClientRequestManager* mInstance;

    bool mIsMyTurn = true;

    ClientRequestManager();
};
