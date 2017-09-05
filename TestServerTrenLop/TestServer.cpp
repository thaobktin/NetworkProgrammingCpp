// TestServer.cpp : Defines the entry point for the console application.
//

// Can than !!! Co cho sai

#include "stdafx.h"

SOCKET		client;
sockaddr_in		sAddr;




int main()
{

	WSAData				wData;
	WORD					wVersion = MAKEWORD(2, 2);

	WSAStartup(wVersion, &wData);

	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	char			addr[100];

	printf(" Nhap dia chi Server: ");
	gets_s(addr);

	printf("\n Nhap so cong: ");
	char cong[10];
	gets_s(cong);
	addrinfo * pHead = NULL;



	getaddrinfo(addr, cong , NULL, &pHead);

	memcpy(&sAddr, pHead->ai_addr, pHead->ai_addrlen);

	freeaddrinfo(pHead);


	connect(client, (SOCKADDR*)&sAddr, sizeof(sAddr));

	char		TenFile[50];
	printf(" Nhap ten file: ");

	gets_s(TenFile);

	printf(" \n Nhap ho va ten: ");
	char				Ten[32];

	gets_s(Ten);

	int		STT;

	printf(" Nhap so tt: ");
	scanf("%d",&STT);

	u_long			filesize;

	FILE *file;
	file = fopen(TenFile, "rb");

	if (file != NULL) {
		fseek(file, 0, SEEK_END);
		filesize = ftell(file);
		fseek(file, 0, SEEK_SET);
	};

	send(client, (char*)&STT, 1, 0);
	send(client, Ten, 32, 0);
	
	send(client, (char*)&filesize,4, 0);

	int ret;
	char buff[1024];
	
	while (!feof(file)) {
		ret = fread(buff, 1, 1024, file);
		if (ret > 0)
			send(client, buff, ret, 0);
	}

	closesocket(client);
	WSACleanup();
	getch();
    return 0;
}

