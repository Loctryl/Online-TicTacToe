#include "Headers/ClientNetWork.h"
#include "Ressources/framework.h"
#include "Headers/MessageWindow.h"


ClientNetWork::ClientNetWork() : Network() { }

ClientNetWork::~ClientNetWork() { }

bool ClientNetWork::Init()
{
    Network::Init(mConnectSocket);

    sockaddr_in clientService = SettingProtocol();

    if (!ConnectServer(clientService))
        return false;

    WSAAsyncSelect(mConnectSocket, MessageWindow::GetHWND(), WM_SOCKET, FD_READ | FD_CLOSE);

    return true;
}

bool ClientNetWork::ConnectServer(sockaddr_in& clientService)
{
    if (connect(mConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService)))
    {
        printf("Erreur connect() %d\n", WSAGetLastError());
        Close();
        return false;
    }

    printf("connexion au serveur reussite\n");
    return true;
}

bool ClientNetWork::SendRequest(std::string data)
{
    bool result = Network::SendRequest(mConnectSocket, data);

    if (!result)
        Close();

    return result;
}

std::string ClientNetWork::Recieve()
{
    std::string result = Network::Receive(mConnectSocket);

    if (result == "")
        Close();

    return result;
}

bool ClientNetWork::Close()
{
    bool closeSuccess = Network::CloseSocket(mConnectSocket);

    WSACleanup();

    return closeSuccess;
}