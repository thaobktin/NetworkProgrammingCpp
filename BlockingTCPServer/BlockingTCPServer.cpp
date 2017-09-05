// BlockingTCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
SOCKET		s, c[1024];
int			nClient = 0;
SOCKADDR_IN	sAddr, cAddr[1024];
// Khai bao than luong
DWORD WINAPI ReceiverThread(LPVOID lpParam)
{
	printf("Luong Receiver bat dau !!!\n");
	char szBuf[1024];
	char szMsg[1024];
	int	 len;
	int i = (int)lpParam;
	int j;
	while (1){
		len = recv(c[i], szBuf, 1024, 0);
		if (len > 0){
			szBuf[len] = 0;
			printf("Client %d:%s", i,szBuf);
			
			sprintf(szMsg, "[%s:%d]:%s", inet_ntoa(cAddr[i].sin_addr),
				ntohs(cAddr[i].sin_port),szBuf);
			for (j = 0; j < nClient;j++)
			if (i != j && c[j] != 0)
				send(c[j], szMsg, strlen(szMsg), 0);
		}
		else
		{
			printf("Client %d ngat ket noi!!! \n", i);
			c[i] = 0;
			break;
		}
	};
	printf("Luong Receiver ket thuc !!!\n");
	return 0;
}
DWORD	WINAPI	SenderThread(LPVOID lParam)
{
	int		i = 0;
	char szBuf[1024];
	char szMsg[1024];
	while (1) {
		printf("S:");
		gets(szBuf);
		sprintf(szMsg,"Server:%s\n",szBuf); //Them dau xuong dong va chu "Server:"
		for (i = 0; i < nClient;i++)
		if (c[i]!=0)
			send(c[i], szMsg, strlen(szMsg), 0);
	};
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2, 2);
	int			ret = WSAStartup(wVersion, &wsaData);

	
	int			cAddrLen = sizeof(cAddr);
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(8888);
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(s, (sockaddr*)&sAddr, sizeof(sAddr)); // Kiem tra loi
	ret = listen(s, 16);// Kiem tra loi
	printf("Dang doi ket noi...\n");
	int		i;
	bool	datachluong = false;
	for (i = 0; i < 1024; i++) c[i] = 0; // Khoi tao mang c
	while (1) {
		for (i = 0; i < nClient; i++) if (c[i] == 0) break;
		c[i] = accept(s, (sockaddr*)&cAddr[i], &cAddrLen);
		printf("Client %i da ket noi !!!\n",i);
		CreateThread(0, 0, ReceiverThread,(LPVOID)i, 0, 0);
		if (i == nClient) nClient++;
		if (datachluong == false)
		{
			CreateThread(0, 0, SenderThread, 0, 0, 0);
			datachluong = true;
		}
	}
	
	
	

	closesocket(s);
	//closesocket(c);
	WSACleanup();
	return 0;
}

