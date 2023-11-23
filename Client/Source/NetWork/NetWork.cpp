#include "NetWork.h"
#include "..\MessageWindow\NetworkMessageWindow.h"
#include "../Thread/NetWorkThread.h"
#include "Utility/Thread/Thread.h"


ClientNetWork::ClientNetWork() : Network() { }

ClientNetWork::~ClientNetWork() { }

bool ClientNetWork::Init(ThreadObj* thread)
{
    return false;
}

bool ClientNetWork::Init(ThreadObj* thread, PCSTR address)
{
    Network::Init(mConnectSocket);

    if (!ConnectServer(address))
        return false;

    WSAAsyncSelect(mConnectSocket, ((ClientNetWorkThread*)thread)->GetWindow()->GetHWND(), WM_SOCKET, FD_READ | FD_CLOSE);

    return true;
}

bool ClientNetWork::ConnectServer(PCSTR address)
{
    sockaddr_in clientService = SettingClientProtocol(address);
    if (connect(mConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService)))
    {
        printf("Erreur connect() %d\n", WSAGetLastError());
        Close();
        return false;
    }

    printf("connexion au serveur reussite\n");
    return true;
}

bool ClientNetWork::SendRequest(std::string data, SOCKET* socket)
{
    bool result = Network::SendRequest(*socket, data);

    //if (!result)
    //    Close();

    return result;
}

std::string ClientNetWork::Recieve(SOCKET* socket)
{
    std::string result = Network::Receive(&mConnectSocket);

    return result;
}

bool ClientNetWork::Close()
{
    bool closeSuccess = Network::CloseSocket(mConnectSocket);

    WSACleanup();

    return closeSuccess;
}