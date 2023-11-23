#include "Headers/ServerWebRequestManager.h"
#include "Headers/WebNetWork.h"

ServerWebRequestManager* ServerWebRequestManager::mInstance = nullptr;

ServerWebRequestManager::ServerWebRequestManager() 
{
    mNetWork = new WebNetWork();
}

ServerWebRequestManager::~ServerWebRequestManager() {}

ServerWebRequestManager* ServerWebRequestManager::GetInstance()
{
    if (mInstance != nullptr) return mInstance;
    mInstance = new ServerWebRequestManager();
    return mInstance;
}

bool ServerWebRequestManager::Init(ThreadObj* thread)
{
    return ((WebNetWork*)mNetWork)->Init(thread);
}

bool ServerWebRequestManager::SendToWeb(std::string request, SOCKET* socket) const
{
    return mNetWork->SendToWeb(*socket, request);
}
