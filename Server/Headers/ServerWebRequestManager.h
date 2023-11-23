#pragma once
#include "Utility/RequestManager/RequestManager.h"
#include "Headers/ServerNetWork.h"
#include "Headers/WebNetWork.h"

class ThreadObj;

class ServerWebRequestManager : public RequestManager
{
public:
    ~ServerWebRequestManager();

    static ServerWebRequestManager* GetInstance();

    bool Init(ThreadObj* thread);

    bool SendToWeb(std::string request, SOCKET* socket) const;

    inline WebNetWork* GetNetWork() { return (WebNetWork*)mNetWork; };

private:
    static ServerWebRequestManager* mInstance;

    ServerWebRequestManager();
};
