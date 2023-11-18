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

    bool SendRequestPlay(int coord[2]) const;
    bool SendRequestValidation(bool validation) const;

    bool RecievePlay(json Message, int* coord);
};
