// UDPSender.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

int _tmain(int argc, _TCHAR* argv[])
{
	// B1
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2, 2);
	int			ret;
	ret = WSAStartup(wVersion, &wsaData);
	// B2
	SOCKET		sender;
	sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// B3
	SOCKADDR_IN	receiverAddr;
	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_port = htons(8888);
	receiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// B4
	char szBuf[1024];
	while (1){
		printf("Nhap vao mot xau:");
		gets(szBuf);
		ret = sendto(sender, szBuf, strlen(szBuf), 0,
			(sockaddr*)&receiverAddr, sizeof(receiverAddr));
		if (ret > 0)
			printf("Da gui %d byte !\n", ret);
		else {
			printf("Loi gui !!!\n");
			break;
		}
	}





	return 0;
}

