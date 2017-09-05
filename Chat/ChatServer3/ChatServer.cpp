// ChatServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

struct ClientInfo {
	SOCKET		c;
	SOCKADDR_IN	cAddr;
	char		szNickname[32];
	bool		bState;
};

ClientInfo * pClients[1024];
int			 nClient = 0;
bool		 bIsStop = false;
SOCKET	s;
DWORD	WINAPI		ClientThread(LPVOID lParam)
{
	int	i = (int)lParam;
	char	szCmd[1024];
	char	szResponse[1024];
	int	 len;
	int j;
	bool kt;
	printf("Client %d dat ket noi !\n", i);
	while (1){
		len = recv(pClients[i]->c, szCmd, 1024, 0);
		if (len > 0){
			szCmd[len - 1] = 0;
			if (strnicmp(szCmd, "login ", 6) == 0){// lenh login
				strcpy(pClients[i]->szNickname, szCmd + 6);

				kt = false;

				for (j = 0; j < nClient;j++)
				if (pClients[j] != 0 && pClients[j]->bState==true && j!=i)
					if (strcmp(pClients[j]->szNickname,pClients[i]->szNickname) == 0){
						kt = true;
						break;
					};

				if (stricmp(pClients[i]->szNickname, "*") == 0) 
					kt = true;

				if (kt == true){
					sprintf(szResponse,"[Error]%s already in use !\n",pClients[i]->szNickname);
					send(pClients[i]->c, szResponse,strlen(szResponse), 0);
				}
				else{
					pClients[i]->bState = true;

					sprintf(szResponse, "[Info]%s logged in!\n",pClients[i]->szNickname);

					printf(szResponse);

					for (j = 0; j < nClient;j++)
					if (pClients[j] != 0 && pClients[j]->bState == true)
						send(pClients[j]->c, szResponse, strlen(szResponse), 0);
				};
				continue;
			}
			if (strnicmp(szCmd, "chat * ", 7) == 0) {// chat *

				if (pClients[i]->bState == false) continue;

				sprintf(szResponse, "[%s]%s\n",pClients[i]->szNickname, szCmd + 7);

				printf(szResponse);

				for (j = 0; j < nClient; j++) 
				if (i != j && pClients[j] != 0 &&pClients[j]->bState == true)
					send(pClients[j]->c, szResponse,strlen(szResponse), 0);

				continue;
			}
			if (strnicmp(szCmd, "chat ", 5)==0){

				char szNickname[32];

				char * pos = NULL;

				pos = strchr(szCmd + 5, ' ');

				if (pos != 0){
					strncpy(szNickname, szCmd + 5, pos - szCmd - 5);

					szNickname[pos - szCmd - 5] = 0;

					for (j = 0; j < nClient;j++)
					if (i != j && pClients[j] != 0 && pClients[j]->bState == true && stricmp(szNickname, pClients[j]->szNickname) == 0){

						sprintf(szResponse, "[%s]%s\n",pClients[i]->szNickname, pos + 1);

						send(pClients[j]->c, szResponse, strlen(szResponse), 0);
					};

					if (stricmp(szNickname, "server") == 0)
						printf("[Private]%s\n", pos + 1);
				};
				continue;
			};
			sprintf(szResponse, "[Error]Unknown command!\n");

			send(pClients[i]->c, szResponse, strlen(szResponse), 0);
		}
		else {
			closesocket(pClients[i]->c);
			delete pClients[i];
			pClients[i] = 0;
			break;
		}
	}
	printf("Client %d ngat ket noi !\n", i);
	return 0;
}
DWORD	WINAPI	SenderThread(LPVOID lParam)
{
	char szXau[1024];
	char szMsg[1024];

	while (1){
		gets_s(szXau);

		if (strnicmp(szXau, "quit", 4) == 0)
		{
			bIsStop = true;
			closesocket(s);
			break;
		}

		sprintf(szMsg, "[Server]%s\n", szXau);

		for (int i = 0; i < nClient;i++)
		if (pClients[i] != 0 && pClients[i]->bState == true)
			send(pClients[i]->c, szMsg, strlen(szMsg), 0);
	};
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA	wsaData;
	WORD	wVersion = MAKEWORD(2, 2);

	int		ret = WSAStartup(wVersion, &wsaData);

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN	sAddr;
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(8888);
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(s, (sockaddr*)&sAddr, sizeof(sAddr));

	ret = listen(s, 16);

	int i;
	int	cAddrLen = sizeof(SOCKADDR_IN);
	for (i = 0; i < 1024; i++) pClients[i] = 0;
	bool bSenderThread = false;
	while (1){
		for (i = 0; i < nClient; i++) if (pClients[i] == 0) break;

		pClients[i] = new ClientInfo;

		pClients[i]->c = accept(s, (sockaddr*)&pClients[i]->cAddr,&cAddrLen);

		if (bIsStop == true) break;

		CreateThread(0, 0, ClientThread, (LPVOID)i, 0, 0);

		if (i == nClient) nClient++;

		if (bSenderThread == false){

			CreateThread(0, 0, SenderThread, 0, 0, 0);
			bSenderThread = true;
		}
	}
	//closesocket(s);
	for (i = 0; i < nClient;i++)

	if (pClients[i] != 0){

		closesocket(pClients[i]->c);

		delete pClients[i];

		pClients[i] = 0;
	};

	WSACleanup();
	printf("Server dat ket thuc !\n");
	getch();
	return 0;
}

