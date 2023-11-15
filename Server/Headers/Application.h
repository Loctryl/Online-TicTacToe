#pragma once

class RequestManager;
class GameManager;

class Application
{
	RequestManager* mRequestManager;

public:
	Application();
	~Application();

	bool Init();

	int Run();
};