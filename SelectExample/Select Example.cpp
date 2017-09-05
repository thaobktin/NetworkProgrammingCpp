// Select Example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA DATA;
	WSAStartup(MAKEWORD(2, 2), &DATA);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bind(s, (sockaddr*)&saddr, sizeof(saddr));
	listen(s, 10);
	fd_set socketset_read;
	SOCKET* carray = NULL;
	int cnumber = 0;

	while (true)
	{
		FD_ZERO(&socketset_read);
		FD_SET(s, &socketset_read);

		for (int i = 0; i < cnumber; i++)
		{
			FD_SET(carray[i], &socketset_read);	
		}

		select(0, &socketset_read, NULL, NULL, NULL);
		if (FD_ISSET(s, &socketset_read))
		{
			SOCKADDR_IN caddr;
			int clen = sizeof(caddr);
			SOCKET c = accept(s, (sockaddr*)&caddr, &clen);
			carray = (SOCKET*)realloc(carray, (cnumber + 1) * sizeof(SOCKET));
			carray[cnumber++] = c;
		}

		for (int i = 0; i < cnumber;i++)
		{
			if (FD_ISSET(carray[i], &socketset_read))
			{
				char* buf = (char*)calloc(1024, 1);
				recv(carray[i], buf, 1024, 0);
				printf("%s\n", buf);
				SleepEx(10000, TRUE);
				send(carray[i], buf, strlen(buf) + 1, 0);
			}
		}
	}
	return 0;
}

