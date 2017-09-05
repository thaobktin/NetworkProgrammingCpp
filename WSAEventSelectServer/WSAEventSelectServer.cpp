// WSAEventSelectServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA	wsaData;
	WORD	wVersion = MAKEWORD(2, 2);
	int		ret = WSAStartup(wVersion, &wsaData);

	SOCKET	s, c[1024];
	SOCKADDR_IN	cAddr[1024];
	int		nClient;
	SOCKADDR_IN sAddr;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(8888);
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(s, (sockaddr*)&sAddr, sizeof(sAddr));

	WSAEVENT	events[1024];
	// events[0] danh cho socket server
	events[0] = WSACreateEvent();
	c[0] = s;

	WSAEventSelect(s, events[0], FD_ACCEPT);
	
	listen(s, 16);
	nClient = 1;
	int i,index,j;
	int	cAddrLen = sizeof(SOCKADDR_IN);
	WSANETWORKEVENTS	networkEvents;
	char szXau[1024];
	int	 len;
	while (1){
		index = WSAWaitForMultipleEvents(nClient, events, FALSE, 
			INFINITE, FALSE);
		index = index - WSA_WAIT_EVENT_0;
		for (i = index; i < nClient; i++)
		{
			ret = WSAWaitForMultipleEvents(1, &events[i], FALSE,
				0, FALSE);
			if (ret == WSA_WAIT_FAILED || ret == WSA_WAIT_TIMEOUT) continue;
			WSAResetEvent(events[i]);
			WSAEnumNetworkEvents(c[i], events[i], &networkEvents);
			if (networkEvents.lNetworkEvents & FD_ACCEPT){
				if (networkEvents.iErrorCode[FD_ACCEPT_BIT] != 0){
					printf("Loi accept !");
					continue;
				};
				c[nClient] = accept(s, (sockaddr*)&cAddr[nClient],
					&cAddrLen);
				printf("Co ket noi moi den, cat vao vi tri %d !\n", nClient);
				
				//WSAResetEvent(events[i]);
				events[nClient] = WSACreateEvent();
				WSAEventSelect(c[nClient], 
					events[nClient],FD_READ|FD_CLOSE);
				nClient++;
			}
			if (networkEvents.lNetworkEvents & FD_READ){
				if (networkEvents.iErrorCode[FD_READ_BIT] != 0)
				{
					printf("Loi FD_READ !");
					continue;
				};
				//WSAResetEvent(events[i]);
				len = recv(c[i], szXau, 1024, 0);
				if (len > 0){
					szXau[len] = 0;
					printf("Client %d:%s\n", i, szXau);
				}
				else
					printf("Client %d ngat ket noi !", i);
			}
			if (networkEvents.lNetworkEvents & FD_CLOSE){
				if (networkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
					printf("Loi FD_CLOSE: %d", 
					networkEvents.iErrorCode[FD_CLOSE_BIT]);
				closesocket(c[i]);
				WSACloseEvent(events[i]);
				printf("Client %d ngat ket noi !\n", i);
				for (j = i; j < nClient - 1; j++)
				{
					c[j] = c[j + 1];
					events[j] = events[j + 1];
				};
				nClient--;
			}

		}
	}




	return 0;
}

