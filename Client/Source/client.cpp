#include "Headers/Application.h"

int main()
{
	Application app = Application();

	if (!app.Init())
		return 1;

	return app.Run();
}