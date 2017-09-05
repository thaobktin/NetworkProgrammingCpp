// DNS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA	wsaData;
	WORD	wVersion = MAKEWORD(2, 2);
	int		ret = WSAStartup(wVersion, &wsaData);

	addrinfo * pHead = NULL,*p;
	SOCKADDR_IN	sResult;
	ret = getaddrinfo("113.171.240.30", "http" /*Dung*/, NULL, &pHead);
	if (ret != 0)
		printf("Loi phan giai : %d!!!", ret);
	else
	{
		p = pHead;
		while (p != NULL)
		{
			memcpy(&sResult, p->ai_addr, p->ai_addrlen);
			printf("Ket qua:%s:%d\n", inet_ntoa(sResult.sin_addr),
				ntohs(sResult.sin_port));
			p = p->ai_next;
		};
		freeaddrinfo(pHead);
	};
	getchar();
	WSACleanup();
	return 0;
}

