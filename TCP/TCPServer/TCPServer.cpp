// TCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string.h>


int _tmain(int argc, _TCHAR* argv[])
{
	// B1 - Khoi tao
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2, 2);
	int			ret = WSAStartup(wVersion, &wsaData);
	// B2 - Tao socket
	SOCKET		s;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// B3 - bind
	SOCKADDR_IN	sAddr;
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(8888);
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY); // ~ 0.0.0.0
	ret = bind(s, (sockaddr*)&sAddr, sizeof(sAddr));
	if (ret == SOCKET_ERROR)
	{
		printf("Loi bind:%d!\n", WSAGetLastError());
		getchar();
		return 0;
	};
	// B4 - listen
	ret = listen(s, 16);
	if (ret == SOCKET_ERROR)
	{
		printf("Loi listen:%d!\n", WSAGetLastError());
		getchar();
		return 0;
	};
	printf("Dang doi ket noi o cong 8888...");
	// B5 - accept
	SOCKET	c, c2;
	SOCKADDR_IN	cAddr;
	int			cAddrLen = sizeof(cAddr);
	c = accept(s, (sockaddr*)&cAddr, &cAddrLen);
	printf("Co ket noi moi !!!\n");
	// B6 - send
	char * szHello = "Xin chao client !!!";
	send(c, szHello, strlen(szHello), 0);
	// B7 - recv
	char	buf[1024];
	int		len = 0;
	while (1)
	{
		len = recv(c, buf, 1024, 0);
		if (len > 0)
		{
			buf[len] = 0;
			printf("Nhan duoc %d byte tu client:%s\n", len, buf);
		}
		else
		{
			printf("Loi ket noi !!!\n");
			break;
		}
		fflush(stdin);
		gets_s(buf);
		len = send(c2, buf, strlen(buf), 0);
		printf("Error: %d", GetLastError());
		if (len > 0)
			printf("Da gui %d byte den client!\n", len);
		else
		{
			printf("Loi ket noi !!!\n");
			break;
		}
	};
	// B8 - closesocket

	closesocket(s);
	closesocket(c);

	// B9 -WSACleanup
	WSACleanup();

	getchar();
	return 0;
}

