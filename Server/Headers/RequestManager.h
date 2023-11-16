#pragma once

class NetWork;

class RequestManager
{
public:
    RequestManager();
    virtual ~RequestManager() = default;

    bool Init();

    bool SendRequest(bool validation) const;
    bool SendRequest(int coord[2]) const;
    bool RecievePlay(int coord[2]);
    bool Close();
    void NextClient();

public:
    NetWork* mNetWork;
};
