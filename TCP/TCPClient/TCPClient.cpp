// TCPClient.cpp : Defines the entry point for the console application.
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
	WSADATA	wsaData;
	WORD	wVersion = MAKEWORD(2, 2);
	int		ret;
	ret = WSAStartup(wVersion, &wsaData);
	// B2 - Tao socket
	SOCKET	c;
	c = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// B3 - Dien dia chi cua server
	SOCKADDR_IN	sAddr;
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(8888);
	sAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// B4 - Ket noi
	ret = connect(c, (SOCKADDR*)&sAddr, sizeof(sAddr));
	if (ret == SOCKET_ERROR){
		printf("Loi ket noi: %d !!!\n", WSAGetLastError());
		getch();
		return 0;
	};
	printf("Da ket noi den server!\n");
	// B5,B6 - Nhan, Gui
	char	szBuf[1024];
	int		len;
	while (1){
		len = recv(c, szBuf, 1024, 0);
		if (len > 0){
			szBuf[len] = 0;
			printf("Server:%s\n", szBuf);
		}
		else break;
		printf("Nhap vao mot xau:");
		fflush(stdin);
		gets_s(szBuf);
		len = send(c, szBuf, strlen(szBuf), 0);
		if (len <= 0) break;
	}
	// B7 - closesocket
	closesocket(c);
	// B8  - WSACleanup
	WSACleanup();
	printf("Xong !");
	getch();
	return 0;
}

