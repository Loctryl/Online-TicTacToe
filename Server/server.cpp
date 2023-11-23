#include "Source/ServApp.h"

int main()
{
	ServApp app = ServApp();

	if (!app.Init())
		return 1;

	return app.Run();
}