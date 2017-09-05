// TCP Thread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <Windows.h>

DWORD WINAPI Send_Recv_Data(LPVOID arg)
{
	SOCKET c = (SOCKET)arg;
	char* str = "Hello";
	send(c, str, strlen(str), 0);
	char buf[1024];
	while (0 == 0)
	{
		memset(buf, 0, 1024);
		recv(c, buf, 1024, 0);
		printf("%s", buf);
		if (strcmp(buf, "exit") == 0)
		{
			printf("Mot client nao do da thoat");
			break;
		}
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA DATA;
	WSAStartup(MAKEWORD(2, 2), &DATA);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bind(s, (sockaddr*)&addr, sizeof(addr));
	listen(s, 5);
	while (0 == 0)
	{
		SOCKADDR_IN caddr;
		int clen = sizeof(caddr);
		SOCKET c = accept(s, (sockaddr*)&caddr, &clen);
		//GUI NHAN DU LIEU
		CreateThread(NULL, 0, Send_Recv_Data, (LPVOID)c, 0, NULL);
	}
	return 0;
}

