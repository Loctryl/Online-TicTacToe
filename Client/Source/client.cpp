#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Headers/Application.h"

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	Application app = Application();

	app.Init();

	return app.Run();
}