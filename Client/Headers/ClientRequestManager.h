#pragma once
#include "Utility/RequestManager/RequestManager.h"
#include "ClientNetWork.h"

class ClientRequestManager : public RequestManager
{
public:
    ~ClientRequestManager();

    static ClientRequestManager* GetInstance();

    bool IsMyTurn() const;

    void Play(int coord[2]);

    bool Init();

    bool ManageMessage(std::string Message);

    inline ClientNetWork* GetNetWork() { return (ClientNetWork*)mNetWork; };

private:
   static ClientRequestManager* mInstance;

   bool mIsMyTurn = false;
   int mMyChoice[2] = {};

    ClientRequestManager();
};
