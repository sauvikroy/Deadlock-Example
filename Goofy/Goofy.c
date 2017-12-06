#include <windows.h>
#include <stdio.h>

CRITICAL_SECTION cs1,cs2;

long WINAPI ThreadFn(long);

int main()
{
	DWORD iThreadID;
	InitializeCriticalSection(&cs1);
	InitializeCriticalSection(&cs2);
	CloseHandle(CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFn,
		NULL,0, &iThreadID));
	(TRUE);
	{
		EnterCriticalSection(&cs1);
		printf("\nThread1 has entered Critical Section 1 but not 2.");
		EnterCriticalSection(&cs2);
		printf("\nThread1 has entered Critical Section 1 and 2!");
		LeaveCriticalSection(&cs2);
		printf("\nThread1 has left Critical Section 2 but still owns 1.");
		LeaveCriticalSection(&cs1);
		printf("\nThread1 has left both critical sections...");
		Sleep(20);
	};

	return(0);
}

long WINAPI ThreadFn(long lParam)
{
	while(TRUE)
	{
		EnterCriticalSection(&cs2);
		printf("\nThread2 has entered Critical Section 2 but not 1.");
		EnterCriticalSection(&cs1);
		printf("\nThread2 has entered Critical Section 2 and 1!");
		LeaveCriticalSection(&cs1);
		printf("\nThread2 has left Critical Section 1 but still owns 2.");
		LeaveCriticalSection(&cs2);
		printf("\nThread2 has left both critical sections...");
		Sleep(20);
	};
}