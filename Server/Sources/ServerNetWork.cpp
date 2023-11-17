#include "Headers\ServerNetWork.h"
#include "Headers/MessageWindow.h"


ServerNetWork::ServerNetWork() { }

bool ServerNetWork::Init()
{
    Network::Init(mListenSocket);

    sockaddr_in serviceServer = SettingProtocol();

    if (!Bind(serviceServer))
        return false;

    if (!WaitClients())
        return false;

    WSAAsyncSelect(mListenSocket, MessageWindow::GetHWND(), WM_SOCKET, FD_ACCEPT);

    return true;
}

bool ServerNetWork::Bind(sockaddr_in& serviceServer)
{
    if (bind(mListenSocket, (SOCKADDR*)&serviceServer, sizeof(serviceServer)) == SOCKET_ERROR)// Associe l'adresse locale au socket
    {
        printf("Erreur bind() %d\n", WSAGetLastError());
        Network::CloseSocket(mListenSocket);
        return false;
    }
    else
        return true;
}

bool ServerNetWork::WaitClients()
{
    if (listen(mListenSocket, NB_CLIENT) == SOCKET_ERROR)
    {
        printf("Erreur lors de l'ecoute : %d\n", WSAGetLastError());
        Network::CloseSocket(mListenSocket);
        return false;
    }

    printf("Attente de la connexion de 2 clients...\n");
    return true;
}

bool ServerNetWork::AcceptClient(int &numClient)
{
    mAcceptSocket[numClient] = accept(mListenSocket, NULL, NULL);
    if (mAcceptSocket[numClient] == INVALID_SOCKET)
    {
        printf("Erreur accept() socket numero %d : %d\n", numClient, WSAGetLastError());
        return false;
    }

    WSAAsyncSelect(mAcceptSocket[numClient], MessageWindow::GetHWND(), WM_SOCKET, FD_READ | FD_CLOSE);

    printf("Client connecte\n");
    return true;
}

bool ServerNetWork::SendRequest(std::string data)
{
    bool result = Network::SendRequest(mAcceptSocket[mActualClient], data);

    if (!result)
        Close();

    return result;
}

std::string ServerNetWork::Recieve()
{
    std::string result = Network::Receive(mAcceptSocket[mActualClient]);

    if (result == "")
        Close();

    return result;
}

bool ServerNetWork::Close()
{
    bool closeSuccess = true;

    for (int i = 0; i < NB_CLIENT; i++)
    {
        if (!Network::CloseSocket(mAcceptSocket[i]))
            closeSuccess = false;
    }

    if (!Network::CloseSocket(mListenSocket))
        closeSuccess = false;

    WSACleanup();

    return closeSuccess;
}

void ServerNetWork::NextClient()
{
    mActualClient = (mActualClient + 1) % NB_CLIENT;
}