#pragma once
#include "Resources/framework.h"

class ThreadObj 
{
protected:
	HANDLE mThread;
	CRITICAL_SECTION mMutex;

public:
	ThreadObj();
	virtual ~ThreadObj();

	DWORD Start();

	void EnterMutex();
	void LeaveMutex();

	bool InitThread();
	void CloseThread();

	inline HANDLE* GetHandle() { return &mThread; };

	virtual void ThreadFunction() = 0;
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);
};