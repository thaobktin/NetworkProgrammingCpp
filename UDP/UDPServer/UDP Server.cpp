// UDP Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA DATA;
	WSAStartup(MAKEWORD(2, 2), &DATA);

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	int error = bind(s, (sockaddr*)&addr, sizeof(addr));
	DWORD ecode = GetLastError();
	listen(s, 5);
	char* buffer = (char*)calloc(1000, 1);
	SOCKADDR_IN caddr;

	while (0 == 0)
	{
		memset(buffer, 0, 1000);
		memset(&caddr, 0, sizeof(caddr));
		int clen = sizeof(caddr);
		int r = recvfrom(	s, 
							buffer, 1000, 0, 
							(sockaddr*)&caddr,
							&clen);
		printf("%s\n", buffer);
	}
	return 0;
}

