// HelloEvent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

HANDLE hEvent = INVALID_HANDLE_VALUE;

DWORD WINAPI helloEvent(LPVOID arg)
{
	SetEvent(hEvent); //Mo khoa
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CreateThread(NULL, 0, helloEvent, NULL, 0, NULL);
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	ResetEvent(hEvent); //Dong khoa
	//Doi khoa mo ra
	WaitForSingleObject(hEvent, INFINITE); 
	return 0;
}

