#pragma once
#include "Utility/RequestManager/RequestManager.h"
#include "Headers/ServerNetWork.h"
#include "Headers/WebNetWork.h"

class ServerRequestManager : public RequestManager
{
public:
    ~ServerRequestManager();

    static ServerRequestManager* GetInstance();

    bool Init(ThreadObj* thread);

    bool ManageMessage(std::string Message, SOCKET* socket);

    inline ServerNetWork* GetNetWork() { return (ServerNetWork*)mNetWork; };

private:
    static ServerRequestManager* mInstance;

    ServerRequestManager();

    bool SendRequestValidation(bool validation, SOCKET* socket) const;

    bool SendRequestWinner(int winner, SOCKET* socket) const;
};
