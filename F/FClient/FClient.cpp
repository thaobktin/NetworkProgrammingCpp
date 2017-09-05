// FClient.cpp : Defines the entry point for the console application.
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
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2, 2);
	int			ret = WSAStartup(wVersion, &wsaData);
	SOCKET		c;
	c = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN	sAddr;
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(8888);
	sAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = connect(c, (sockaddr*)&sAddr, sizeof(sAddr));
	Packet	pk_send;
	Packet	pk_receive;
	char	szFilename[1024];
	int		dwFilesize;
	printf("Nhap ten file can gui:");
	gets_s(szFilename);
	FILE * fp = fopen(szFilename, "rb");
	if (fp != NULL){
		fseek(fp, 0, SEEK_END);
		dwFilesize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
	};
	pk_send.bCmd = 0;
	pk_send.wLenth = 255 + 4;
	ret = send(c, (char*)&pk_send.bCmd, sizeof(pk_send.bCmd), 0);
	ret = send(c, (char*)&pk_send.wLenth, sizeof(pk_send.wLenth), 0);
	ret = send(c, szFilename, 255, 0);
	ret = send(c, (char*)&dwFilesize, sizeof(dwFilesize), 0);

	recv(c, (char*)&pk_receive.bCmd, sizeof(pk_receive.bCmd), MSG_WAITALL);
	recv(c, (char*)&pk_receive.wLenth, sizeof(pk_receive.wLenth), MSG_WAITALL);
	if (pk_receive.wLenth > 0)
		recv(c, (char*)pk_receive.bData, pk_receive.wLenth, MSG_WAITALL);
	if (pk_receive.bCmd == 1)	// Server dong y nhan file
	{
		char szBuf[8096];
		printf("Server dong y nhan file !. Bat dau gui file...");
		while (!feof(fp)){
			ret = fread(szBuf, 1, 8096, fp);
			if (ret > 0){
				pk_send.bCmd = 3;
				pk_send.wLenth = ret;
				send(c, (char*)&pk_send.bCmd, sizeof(pk_send.bCmd), 0);
				send(c, (char*)&pk_send.wLenth, sizeof(pk_send.wLenth), 0);
				send(c, szBuf, ret, 0);
				printf(".");
			}
		}
		printf("Gui xong file !");



	}
	if (pk_receive.bCmd == 2)
	{
		printf("Server tu choi nhan file. Huy qua trinh gui file !");
	}

	getch();

	return 0;
}

