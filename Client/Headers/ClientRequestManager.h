#pragma once

class ClientNetWork;

class ClientRequestManager
{
public:
    ClientRequestManager();
    virtual ~ClientRequestManager() = default;

    bool Init();

    bool SendRequest(int coord[2]);
    bool RecieveValidation(bool &validation);
    bool RecievePlay(int coord[2]);
    bool Close();

private:
    ClientNetWork* mNetWork;
};
