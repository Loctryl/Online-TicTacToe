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

bool ServerNetWork::AcceptClient(SOCKET* socket)
{
    *socket = accept(mListenSocket, NULL, NULL);
    if (*socket == INVALID_SOCKET)
    {
        printf("Erreur accept() socket : %d\n", WSAGetLastError());
        return false;
    }

    WSAAsyncSelect(*socket, MessageWindow::GetHWND(), WM_SOCKET, FD_READ | FD_CLOSE);

    printf("Client connecte\n");
    return true;
}

bool ServerNetWork::SendRequest(std::string data, SOCKET* socket)
{
    bool result = Network::SendRequest(*socket, data);

    if (!result)
        Close();

    return result;
}

std::string ServerNetWork::Recieve(SOCKET* socket)
{
    std::string result = Network::Receive(socket);

    return result;
}

bool ServerNetWork::Close()
{
    bool closeSuccess = true;

    if (!Network::CloseSocket(mListenSocket))
        closeSuccess = false;

    WSACleanup();

    return closeSuccess;
}