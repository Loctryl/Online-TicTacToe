
#include <iostream>
#include <ostream>
#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib");

#define PORT "80"

using namespace std;

int main()
{
    const string request = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
    
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
    
    SOCKET socks = INVALID_SOCKET;
    char buffer[16*1024] = { 0 };
    sockaddr_in servAddress;
    addrinfo hint;
    PADDRINFOA result;
    ZeroMemory( &hint, sizeof(hint) );
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;

    char argv[50] = "google.com";
    int iResult = getaddrinfo(argv, PORT, &hint, &result);
    if( iResult != 0)
    {
        cout << "address info is not good : " << iResult << endl;
        WSACleanup();
        return -1;
    }

    socks = socket(result->ai_family, result->ai_socktype,result->ai_protocol);
    if(socks == 0 )
    {
        cout<< "\n socket is not good" << endl;
        return -1;
    }
    
    iResult = connect(socks,result->ai_addr, (int)result->ai_addrlen);
    if(iResult < 0)
    {
        cout<< "\n connection is not good" << endl;
        return -1;
    }
    
    if(send(socks, request.c_str(), strlen(request.c_str())+1, 0) < 0){
        cout<<"\n request is not good"<<endl;
        return -1;
    }

    do
    {
        iResult = recv(socks, buffer, 16*1024,0);
        if(iResult > 0)
            cout<< buffer << endl;
        else if ( iResult == 0)
            cout<< "\n Connection close" << endl;
        else
            cout<< "Failed" << endl;
    } while (iResult > 0);
    
    closesocket(socks);
}
