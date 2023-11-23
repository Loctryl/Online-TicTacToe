#include "Thread.h"

Thread::Thread()
{
}

Thread::~Thread()
{
}

void Thread::EnterMutex()
{
	EnterCriticalSection(mMutex);// pour bloquer un bloc d'instructions
}

void Thread::LeaveMutex()
{
	LeaveCriticalSection(mMutex);// pour lib�rer le bloc
}

bool Thread::Init()
{
	InitializeCriticalSection(mMutex);// pour creer la critical section

	if (*mThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		ThreadFunction,	// thread function name
		this,					// argument to thread function 
		CREATE_SUSPENDED,		// Attend l'appel de ResumeThread pour ex�cuter le thread
		NULL))					// returns the thread identifier
		return true;

	return false;
}

void Thread::CloseThread()
{
	DeleteCriticalSection(mMutex);// quand c'est fini
	CloseHandle(mThread);
}


DWORD __stdcall Thread::ThreadFunction(LPVOID lpParam)
{
	Thread* currentThread = (Thread*)lpParam;
	currentThread->ThreadFunction();
	return 0;
}
