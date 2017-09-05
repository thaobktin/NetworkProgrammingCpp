// UDP Sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA DATA;
	WSAStartup(MAKEWORD(2, 2), &DATA);

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	char* str = "Hello UDP";

	while (0 == 0)
	{
		sendto(s, str, strlen(str), 0, (sockaddr*)&addr, sizeof(addr));
		Sleep(1000);
	}

	return 0;
}

