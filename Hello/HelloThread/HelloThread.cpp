// HelloThread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
int flag = 0;

DWORD WINAPI helloThread(LPVOID arg)
{
	printf("Hello Thread\r\n");
	flag += 1;
	return 0;
}

DWORD WINAPI helloThread1(LPVOID arg)
{
	printf("Hello Thread 1\r\n");
	flag += 1;
	return 0;
}

DWORD WINAPI helloThread2(LPVOID arg)
{
	printf("Hello Thread 2\r\n");
	flag += 1;
	return 0;
}

void WaitForExitFlag()
{
	while (flag < 3) //Doi ham helloThread chay xong
	{
		Sleep(100);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	flag = 0;
	HANDLE thread = CreateThread
	(
		NULL,
		0,
		helloThread,	//Dia chia ham bat dau thuc thi
		NULL,			//Tham so cua ham muon thuc thi
		0,
		NULL
	);
	HANDLE thread1 = CreateThread
		(
		NULL,
		0,
		helloThread1,	//Dia chia ham bat dau thuc thi
		NULL,			//Tham so cua ham muon thuc thi
		0,
		NULL
		);
	HANDLE thread2 = CreateThread
		(
		NULL,
		0,
		helloThread2,	//Dia chia ham bat dau thuc thi
		NULL,			//Tham so cua ham muon thuc thi
		0,
		NULL
		);

	HANDLE obj[3] = {thread, thread1, thread2};

	//WaitForExitFlag();	
	WaitForMultipleObjects(3, obj, true, INFINITE);

	return 0;
}

