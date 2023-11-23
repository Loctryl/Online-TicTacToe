#include "Thread.h"

ThreadObj::ThreadObj()
{
}

ThreadObj::~ThreadObj()
{
}

void ThreadObj::EnterMutex()
{
	EnterCriticalSection(&mMutex);// pour bloquer un bloc d'instructions
}

void ThreadObj::LeaveMutex()
{
	LeaveCriticalSection(&mMutex);// pour lib�rer le bloc
}

bool ThreadObj::InitThread()
{
	InitializeCriticalSection(&mMutex);// pour creer la critical section

	mThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		ThreadFunction,	// thread function name
		this,					// argument to thread function 
		CREATE_SUSPENDED,		// Attend l'appel de ResumeThread pour ex�cuter le thread
		NULL);					// returns the thread identifier

	cout << "here";

	return true;
}

void ThreadObj::CloseThread()
{
	DeleteCriticalSection(&mMutex);// quand c'est fini
	CloseHandle(mThread);
}


DWORD __stdcall ThreadObj::ThreadFunction(LPVOID lpParam)
{

	ThreadObj* currentThread = (ThreadObj*)lpParam;
	if(currentThread != nullptr)
		currentThread->ThreadFunction();
	return 0;
}
