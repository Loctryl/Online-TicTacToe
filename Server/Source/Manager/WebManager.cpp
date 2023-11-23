#include "WebManager.h"
#include "NetManager.h"
#include "Grid/Grid.h"
#include "Grid/Player.h"
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
	std::ifstream webserverheader("Resources/webserverheader.txt", std::ios::binary | std::ios::ate);
	std::ifstream webserverfooter("Resources/webserverfooter.txt", std::ios::binary | std::ios::ate);

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
	std::string body = R"(<h1 style="font-size: 70px; color: #FFF1D6; text-align: center;">TIC TAC TOE</h1>)";

	for (auto game : Games) {

		body +=
			R"(<div><div style="display: flex; justify-content: center;"><div>)";

		if (game->mPlayers[0] != nullptr) {

			body += R"(<p style : "font-size: 20px">)" +
				game->mPlayers[0]->mNickName +
				R"(</p>)" +
				CreateGridElement(3, game->mPlayers[0]->mInGameId);
		}
		else {
			body += R"(<p style : "font-size: 20px"> NONE </p>)" +
				CreateGridElement(3, -1);
		}

		body +=
			R"(</div><div style = "padding: 0% 10% 5% 10%"><p style : "font-size: 20px; text-align: center">game id :)" +
			std::to_string(game->mGameId) +
			R"(</p>)";


		for (int i = 0; i < game->mSize; i++) {
			body += R"(<div style="display:flex">)";
			for (int j = 0; j < game->mSize; j++) {
				body += CreateGridElement(3, game->mMainGrid[j][i]);
			}
			body += R"(</div>)";
		}

		body +=
			R"(</div><div>)";

		if (game->mPlayers[1] != nullptr) {


			body +=
				R"(<p style:"font-size: 20px">)" +
				game->mPlayers[1]->mNickName +
				R"( </p>)" +
				CreateGridElement(3, game->mPlayers[1]->mInGameId);
		}
		else {
			body += R"(<p style : "font-size: 20px"> NONE </p>)" +
				CreateGridElement(3, -1);
		}

		body += R"(</div></div></div>)";
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

std::string WebManager::CreateGridElement(int size, int value)
{
	std::string message = "";
	message += R"(<div style=")";

	switch (value)
	{
	case 0:
		message += "background-color : #AD3A23;";
		break;
	case 1:
		message += "background-color : #23AD8B;";
		break;
	default:
		message += "background-color : #CECAC5;";
		break;
	}

	message += "width: " + std::to_string(size) + "vw; height: " + std::to_string(size) + "vw; border: solid 2px #82807E; \"> </div>";

	return message;
}
