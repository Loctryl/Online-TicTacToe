#pragma once
#include <Windows.h>

class Thread 
{
	HANDLE* mThread;
	CRITICAL_SECTION* mMutex;

public:
	Thread();
	virtual ~Thread();

	void EnterMutex();
	void LeaveMutex();

	bool Init();
	void CloseThread();

	inline HANDLE* GetHandle() { return mThread; };

	virtual void ThreadFunction() = 0;
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);
};