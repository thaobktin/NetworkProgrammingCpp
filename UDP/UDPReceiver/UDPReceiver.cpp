// UDPReceiver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

int _tmain(int argc, _TCHAR* argv[])
{
	// B1
	WSADATA	wsaData;
	WORD	wVersion = MAKEWORD(2, 2);
	int		ret;
	ret = WSAStartup(wVersion, &wsaData);
	//B2 
	SOCKET	receiver;
	receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//B3
	SOCKADDR_IN	receiverAddr;
	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_port = htons(8899);
	receiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(receiver, (sockaddr*)&receiverAddr, 
		sizeof(receiverAddr));
	//B4
	SOCKADDR_IN senderAddr;
	SOCKADDR_IN	senderAddrs[1024];
	int         senderCount = 0;
	char		nicknames[1024][32];

	int			senderAddrLen = sizeof(senderAddr);
	char		szBuf[1024];
	int			len,i,vt;
	bool		kt;
	char		msg[1024];
	while (1) {
		len = recvfrom(receiver, szBuf, 1024, 0,
			(sockaddr*)&senderAddr, &senderAddrLen);
		if (len > 0){
			szBuf[len] = 0;
			/*
			printf("[%s:%d]:%s\n", 
				inet_ntoa(senderAddr.sin_addr), 
				ntohs(senderAddr.sin_port),
				szBuf);
			*/
			kt = false;
			vt = 0;
			for (i = 0; i < senderCount;i++)
			if (senderAddr.sin_addr.s_addr ==
				senderAddrs[i].sin_addr.s_addr &&
				senderAddr.sin_port == senderAddrs[i].sin_port)
			{
				kt = true;
				vt = i;
				break;
				
			};
			if (kt == false) {
				senderAddrs[senderCount] = senderAddr;
				szBuf[len - 1] = 0;
				strcpy(nicknames[senderCount], szBuf);
				senderCount++;
				sprintf(msg, "%s vua dang nhap !\n", szBuf);
			}
			else
				sprintf(msg, "%s:%s\n", nicknames[vt], szBuf);
			printf("%s", msg);
				//printf("%s:%s\n", nicknames[vt], szBuf);
			for (i = 0; i < senderCount; i++)
				sendto(receiver, msg, strlen(msg), 0, (sockaddr*)
				&senderAddrs[i], sizeof(senderAddr));

		}
	}


	return 0;
}

