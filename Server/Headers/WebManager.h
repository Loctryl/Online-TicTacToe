#pragma once

#include <string>

class WebManager
{
public:
	static WebManager* GetInstance();

	std::string BuildWebsite();
	std::string BuildBody();
	std::string ReadFile(std::ifstream* file);

private:
	static WebManager* mInstance;
};

