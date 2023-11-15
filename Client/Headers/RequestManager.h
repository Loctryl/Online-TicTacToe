#pragma once

class NetWork;

class RequestManager
{
public:
    RequestManager();
    virtual ~RequestManager() = default;

    bool Init();

    bool SendRequest(int coord[2]);
    bool RecieveValidation(bool &validation);
    bool RecievePlay(int coord[2]);
    bool Close();

private:
    NetWork* mNetWork;
};
