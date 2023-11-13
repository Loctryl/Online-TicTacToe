#include <ostream>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define PORT "80"
#define DEFAULT_BUFLEN 512

int main()
{
    int iResult;
    WSADATA wsaData;
    addrinfo *result = NULL, *ptr = NULL, hints;

    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN];

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    char adrr[100] = "google.com";
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    iResult = getaddrinfo(adrr, PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    ptr = result;

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Connect to server.
    iResult = connect(ConnectSocket, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen));
    if (iResult == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    const char *sendbuf = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
    
    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int) strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    
    // Should really try the next address returned by getaddrinfo
    // if the connect call failed
    // But for this simple example we just free the resources
    // returned by getaddrinfo and print an error message

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    do
    {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        for(auto c : recvbuf)
            std::cout << c;
    }while (iResult > 0);

    closesocket(ConnectSocket);

    return 0;
}
