// FileServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

struct Packet{
	BYTE	bCmd;
	WORD	wLenth;
	BYTE	bData[8096];
};
SOCKET	s, c[1024];
SOCKADDR_IN	cAddr[1024];
int		nClient = 0;

DWORD	WINAPI	ClientThread(LPVOID lParam)
{
	Packet pk;
	int		i = (int)lParam;
	int		len;
	char	szFilename[256];
	int		dwFilesize,dwBytesReceived = 0;
	char	answer;
	Packet	response_pk;
	FILE *  fp = NULL;
	printf("Client %d da ket noi !\n");
	while (1){
		len = recv(c[i], (char*)&pk.bCmd, sizeof(pk.bCmd), MSG_WAITALL);
		
		if (len < sizeof(pk.bCmd)) break;

		len = recv(c[i], (char*)&pk.wLenth, sizeof(pk.wLenth), MSG_WAITALL);

		if (len < sizeof(pk.wLenth)) break;

		len = recv(c[i], (char*)pk.bData, pk.wLenth, MSG_WAITALL);

		if (len < pk.wLenth) break;

		if (pk.bCmd == 0){
			strncpy(szFilename, (char*)pk.bData, 255);
			szFilename[255] = 0;
			memcpy(&dwFilesize, pk.bData + 255, 4);
			printf("Client %d muon gui file %s, kich thuoc %d byte. Co nhan khong(Y/N) ?", 
				i, szFilename, dwFilesize);
			scanf("%c", &answer);
			if (answer == 'Y'||answer=='y'){
				response_pk.bCmd = 1;
				response_pk.wLenth = 0;
				fp = fopen(szFilename, "wb");
				printf("Dang nhan file...");
				dwBytesReceived = 0;

			}
			else{
				response_pk.bCmd = 2;
				response_pk.wLenth = 0;

			};
			send(c[i], (char*)&response_pk.bCmd, sizeof(pk.bCmd), 0);
			send(c[i], (char*)&response_pk.wLenth, sizeof(pk.wLenth), 0);

		}
		if (pk.bCmd == 3)
		{
			fwrite(pk.bData, 1, pk.wLenth, fp);
			printf(".");
			dwBytesReceived += pk.wLenth;
			Sleep(10);
			if (dwBytesReceived == dwFilesize)
			{
				printf("Xong !");
				fclose(fp);
			};
		};

	}
	printf("Client %d ngat ket noi !\n", i);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA	wsaData;
	WORD	wVersion = MAKEWORD(2, 2);
	int		ret = WSAStartup(wVersion, &wsaData);
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN		sAddr;
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(8888);
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(s, (sockaddr*)&sAddr, sizeof(sAddr));
	ret = listen(s, 16);
	int i = 0;
	int	cAddrLen = sizeof(SOCKADDR_IN);
	memset(c, 0, sizeof(SOCKET)* 1024); // Xoa mang c ve 0
	while (1){
		for (i = 0; i < nClient; i++) if (c[i] == 0) break;
		c[i] = accept(s, (sockaddr*)&cAddr[i], &cAddrLen);
		CreateThread(0, 0, ClientThread, (LPVOID)i, 0, 0);
		if (i == nClient) nClient++;
	}

	return 0;
}

