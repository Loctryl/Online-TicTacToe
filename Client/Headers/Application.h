#pragma once
#include "GameManager.h"
#include "RequestManager.h"

class Application
{
	RequestManager mRequestManager;
	GameManager mGame;

public:
	Application();
	~Application();

	bool Init();

	int Run();
};

