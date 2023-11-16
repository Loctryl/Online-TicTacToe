#include "Headers/ServApp.h"
#include <Headers/json.hpp>
#include "..\Headers\ServerNetWork.h"
#include "Headers/ServerRequestManager.h"

using json = nlohmann::json;

ServApp::ServApp()
{
	mRequestManager = new ServerRequestManager();
}

ServApp::~ServApp() { }

bool ServApp::Init()
{
	return mRequestManager->Init();
}

int ServApp::Run()
{
	int coord[2];

	bool endGame = false;
	bool validation = false;

	// ENVOI DE LA VALIDATION DE LANCEMENT DE JEU
	if (!mRequestManager->SendRequest(validation))
		return 1;
	mRequestManager->NextClient();
	if (!mRequestManager->SendRequest(validation))
		return 1;
	mRequestManager->NextClient();

	std::string Message = "";

	while (!endGame)
	{
		Message = mRequestManager->mNetWork->Recieve();
		if (Message == "") continue;

		json parsedMessage = json::parse(Message);
		if (parsedMessage["type"] == "play") {
			coord[0] = parsedMessage["x"];
			coord[1] = parsedMessage["y"];

			// test du deplacement --> validation = true/false
			validation = true;

			if (validation) {
				mRequestManager->NextClient();
				mRequestManager->SendRequest(coord);
			}
			else {
				json answer = {
					{"type", "answer"},
					{"answer", validation}
				};
				mRequestManager->mNetWork->SendRequest(answer.dump().c_str());
			}
		}
		// RECEPTION D'UN DEPLACEMENT
		//if (!mRequestManager->RecievePlay(coord))
		//	return 1;


		// ENVOI DE LA VALIDATION
		//if (!mRequestManager->SendRequest(validation))
		//	return 1;

		//if (validation)
		//{
		//	// faire le deplacement
		//	// MAj endGame
		//	mRequestManager->NextClient();

		//	// ENVOI DU DEPLACEMENT A L'AUTRE JOUEUR
		//	if (!mRequestManager->SendRequest(coord))
		//		return 1;
		//}
	}

	// FERMETURE DU SERVER
	if (!mRequestManager->Close())
		return 1;

	return 0;
}