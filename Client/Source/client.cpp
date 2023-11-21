#include "..\Headers\ClientApp.h"

int main()
{
	ClientApp app = ClientApp();

	if (!app.Init())
		return 1;

	return app.Run();
}