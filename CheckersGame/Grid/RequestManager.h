#pragma once

class RequestManager
{
public:
	RequestManager();
	virtual ~RequestManager();

	bool Send(SOCKET socket, const char* sendBuff, size_t bufferSizeData);
	const char* Recieve(SOCKET socket);
};
