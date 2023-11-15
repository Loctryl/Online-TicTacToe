#pragma once
#include "NetWork.h"

class RequestManager
{
public:
    RequestManager();
    virtual ~RequestManager();

    bool Init();

    bool SendRequest(int coord[2]);
    bool RecieveValidation(bool &validation);
    bool RecievePlay(int coord[2]);
    bool Close();

private:
    NetWork mNetWork;
};
