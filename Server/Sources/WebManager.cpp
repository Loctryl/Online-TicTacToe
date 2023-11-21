#include "Headers/WebManager.h"
#include "Headers/NetManager.h"
#include "Grid/Grid.h"
#include "Grid/Player.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

WebManager* WebManager::mInstance = nullptr;

WebManager* WebManager::GetInstance()
{
	if (mInstance == nullptr) {
		mInstance = new WebManager();
	}
	return mInstance;
}

std::string WebManager::BuildWebsite()
{
	std::ifstream webserverheader("./Sources/webserverheader.txt", std::ios::binary | std::ios::ate);
	std::ifstream webserverfooter("./Sources/webserverfooter.txt", std::ios::binary | std::ios::ate);

	std::string webserverheaderstring = ReadFile(&webserverheader);
	std::string webserverbodystring = BuildBody();
	std::string webserverfooterstring = ReadFile(&webserverheader);

	size_t webserverlength;
	std::string response = "";

	webserverlength = webserverheaderstring.length() + webserverbodystring.length() + webserverfooterstring.length(); // + data length
	response = "HTTP/1.1 200 OK\r\nServer: TikTakToeHost\r\nContent-Length: " + std::to_string(webserverlength) + "\r\nContent-Type: text/html\r\n\r\n" + webserverheaderstring + webserverbodystring + webserverfooterstring;

	return response;
}

std::string WebManager::BuildBody()
{
	std::vector<Grid*> Games = NetManager::GetInstance()->GetGames();
	std::string body = "";

	for (auto game : Games) {

		body +=
			R"(<div class = "game"><div class = "player"> <p>)" +
			game->mPlayers[0]->mNickName +
			R"( < / p> <div class="case)" +
			std::to_string(game->mPlayers[0]->mInGameId) +
			R"("> </div>< / div> <div class = "grid">)";


		for (int i = 0; i < game->mSize; i++) {
			body += R"(<div class"row">)";
			for (int j = 0; j < game->mSize; j++) {
				body += 
					R"(< div class = "case)" +
					std::to_string(game->mMainGrid[i][j]) +
					R"(> < / div>)";
			}
			body += R"(</div>)";
		}

		body +=
			R"(</div><div class = "player"><p>)" +
			game->mPlayers[1]->mNickName +
			R"( < / p><div class = "case)" +
			std::to_string(game->mPlayers[1]->mInGameId) +
			R"("> < / div>< / div>)";
	}
	return body;
}

std::string WebManager::ReadFile(std::ifstream* file)
{
	std::stringstream webserverbuffer;
	std::string webserverstring;

	(*file).seekg(0, std::ios::beg);
	webserverbuffer << (*file).rdbuf();
	webserverstring = webserverbuffer.str();
	return webserverstring;
}
