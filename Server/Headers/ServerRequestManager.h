#pragma once

class ClientNetWork;

class ServerRequestManager
{
public:
    ServerRequestManager();
    virtual ~ServerRequestManager() = default;

    bool Init();

    bool SendRequest(bool validation) const;
    bool SendRequest(int coord[2]) const;
    bool RecievePlay(int coord[2]);
    bool Close();
    void NextClient();

public:
    ClientNetWork* mNetWork;
};
