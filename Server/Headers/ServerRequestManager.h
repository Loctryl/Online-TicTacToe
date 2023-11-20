#pragma once

#include "Utility/RequestManager/RequestManager.h"

class ServerRequestManager : public RequestManager
{
public:
    ~ServerRequestManager();

    static ServerRequestManager* GetInstance();

    bool Init();
    void NextClient() const;

    bool ManageMessage(std::string Message);

private:
    static ServerRequestManager* mInstance;

    ServerRequestManager();

    bool SendRequestValidation(bool validation) const;
};
