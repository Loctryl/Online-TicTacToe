#include <Headers/json.hpp>
#include "Headers/RequestManager.h"
using json = nlohmann::json;

RequestManager::RequestManager() : mNetWork(NetWork())
{
}

RequestManager::~RequestManager()
{
}

bool RequestManager::Init()
{
	return mNetWork.Init();
}

bool RequestManager::SendRequest(int coord[2])
{
	std::string data = "{ \"x\": \"";
	data += coord[0];
	data += "\", \"y\": \"";
	data += coord[1];
	data += "\" }";

	return mNetWork.SendRequest(data.c_str());
}

bool RequestManager::RecieveValidation(bool &validation)
{
	const char* data = mNetWork.Recieve();

	if (data == nullptr)
		return false;
	
	json parsedMessage = json::parse(data);
	validation = parsedMessage["answer"];
	return true;
}

bool RequestManager::RecievePlay(int coord[2])
{
	const char* data = mNetWork.Recieve();

	if (data == nullptr)
		return false;
	
	json parsedMessage = json::parse(data);
	coord[0] = parsedMessage["x"];
	coord[1] = parsedMessage["y"];
	return true;
}

bool RequestManager::Close()
{
	return mNetWork.Close();
}
