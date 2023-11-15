#include <GameManager.h>

void Oui()
{
	cout << "oui" << endl;
}

int main()
{
	GameManager g = GameManager();
	
	g.InitGame(5);

	int x, y;
	x = -1;
	y = -1;

	Event event{};
	while (g.IsWindowOpened())
	{
		while (g.mWindow->GetWindow()->pollEvent(event))
		{
			if (g.IsPressEsc(&event)) g.mWindow->GetWindow()->close();
			if(g.IsMouseClick(&event) && g.IsMove(&x, &y)) {
				g.Play(x, y, &Oui);

				x = -1;
				y = -1;
			}
		}
		g.RenderGame();
	}
}