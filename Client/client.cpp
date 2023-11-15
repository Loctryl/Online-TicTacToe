#include <ostream>
#include <iostream>
#include "Source/NetWork.h"

int main()
{
    NetWork network = NetWork();
    network.Init();
    network.SendRequest("GET / HTTP/1.1\r\nHost: google.com\r\nConnection: close\r\n\r\n");
    network.Recieve();
    return 0;
}
