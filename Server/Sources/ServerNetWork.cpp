#include "Headers\ServerNetWork.h"
#include "Headers/MessageWindow.h"

ServerNetWork::ServerNetWork() { }

bool ServerNetWork::Init()
{
    Network::Init(mListenSocket);

    sockaddr_in serviceServer = SettingProtocol();

    if (!Bind(serviceServer, &mListenSocket))
        return false;

    if (!WaitClients())
        return false;

    WSAAsyncSelect(mListenSocket, MessageWindow::GetHWND(), WM_SOCKET, FD_ACCEPT);
    return true;
}

bool ServerNetWork::WebInit()
{
    Network::Init(mWebSocket);

    sockaddr_in service = SettingWebProtocol();

    if (!Bind(service, &mWebSocket))
        return false;

    if (listen(mWebSocket, 1) == SOCKET_ERROR)
    {
        printf("Erreur lors de l'ecoute : %d\n", WSAGetLastError());
        Network::CloseSocket(mListenSocket);
        return false;
    }

    WSAAsyncSelect(mWebSocket, MessageWindow::GetHWND(), WM_WEBSOCKET, FD_ACCEPT);

    return true;
}

bool ServerNetWork::ConnectServer(sockaddr_in& clientService)
{
    if (connect(mWebSocket, (SOCKADDR*)&clientService, sizeof(clientService)))
    {
        printf("Erreur connect() %d\n", WSAGetLastError());
        Close();
        return false;
    }

    printf("connexion au serveur reussite\n");
    return true;
}

bool ServerNetWork::Bind(sockaddr_in& serviceServer, SOCKET* socket)
{
    if (bind(*socket, (SOCKADDR*)&serviceServer, sizeof(serviceServer)) == SOCKET_ERROR)// Associe l'adresse locale au socket
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

bool ServerNetWork::AcceptWebClient(SOCKET* socket)
{
    *socket = accept(mWebSocket, NULL, NULL);
    if (*socket == INVALID_SOCKET)
    {
        printf("Erreur accept() socket : %d\n", WSAGetLastError());
        return false;
    }

    printf("Client Web connecte\n");
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