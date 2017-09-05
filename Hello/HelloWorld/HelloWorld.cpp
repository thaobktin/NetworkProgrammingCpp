// HelloWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2, 2);
	int			ret = 0;

	ret = WSAStartup(wVersion, &wsaData);
	if (ret == SOCKET_ERROR)
		printf("Khoi tao that bai.Loi:%d !\n",
			WSAGetLastError());
	else
		printf("Khoi tao thanh cong !\n");
	
	SOCKET	s1, s2;
	s1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	s2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (s1 != SOCKET_ERROR)
		printf("Da tao xong socket s1 = %d\n", s1);
	else
		printf("Khong tao duoc s1!!!");
	
	if (s2 != SOCKET_ERROR)
		printf("Da tao xong socket s2 = %d\n", s2);
	else
		printf("Khong tao duoc s2!!!");


	// Dien dia chi 192.168.1.10:8888
	SOCKADDR_IN	sAddr;
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(8888);  // 1 - 65535
	sAddr.sin_addr.s_addr = inet_addr("192.168.1.10");// Dung




	ret = WSACleanup();
	if (ret == SOCKET_ERROR)
	{	
		printf("Giai phong that bai.Ma loi:%d !\n",
			WSAGetLastError());
	}
	else
		printf("Giai phong thanh cong !\n");

	getch();
	return 0;
}

