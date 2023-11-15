#pragma once

class RequestManager;
class GameManager;

class Application
{
	RequestManager* mRequestManager;
	GameManager* mGame;

public:
	Application();
	~Application();

	bool Init();

	int Run();
};