// GiaiMa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "stdio.h"
#include "winsock2.h"
#include "ws2tcpip.h"


SOCKET s, c[1204];
int nClient = 0;
SOCKADDR_IN sAddr;
SOCKADDR_IN cAddr;

DWORD WINAPI SenderThread(LPVOID Param) {
	char buf[1024];
	char msg[1024];
	while (true) {
		fgets(buf, 1024, stdin);
		sprintf(msg, "Server: %s\n", buf);
		for (int i = 0; i < nClient; i++)
			if (c[i != 0]) {
				send(c[i], msg, strlen(msg), 0);
			}
	}
	return 0;
}

char Reverse(char strInput[])
{
	for (int i = 0; i++; i < strlen(strInput))
	{

	}
}

int main()
{
	WSADATA wsadata;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (ret == SOCKET_ERROR) printf("Create winsock fail.");
	else printf("Create winsock success.\n");

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(10008);
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int clientlen = sizeof(cAddr);

	for (int j = 0; j < 1024; j++) {
		c[j] = 0;
	}


	c[0] = s;
	nClient = 1;

	ret = bind(s, (sockaddr*)&sAddr, sizeof(sAddr));
	ret = listen(s, 16);

	fd_set fdread;
	int i;
	char buf[1024];
	char msg[1024];
	int len;
	timeval tm;
	bool tachluong = false;

	while (true) {
		FD_ZERO(&fdread);
		FD_SET(s, &fdread);
		for (i = 0; i < nClient; i++) {
			if (c[i] != 0) FD_SET(c[i], &fdread);
		}

		tm.tv_sec = 5;
		tm.tv_usec = 0;

		ret = select(0, &fdread, 0, 0, &tm);
		if (ret == SOCKET_ERROR) break;
		if (ret == 0) {
			printf("Khong co su kien nao xay ra\n");
			continue;
		}
		if (FD_ISSET(s, &fdread)) {
			for (i = 1; i < nClient; i++)
				if (c[i] == 0) break;
			c[i] = accept(s, (sockaddr*)&cAddr, &clientlen);
			printf("Client %d connectd\n", i);
			char * szHello = "Hello client\n";
			send(c[i], szHello, strlen(szHello), 0);
			if (tachluong == false) {
				CreateThread(0, 0, SenderThread, 0, 0, 0);
				tachluong = true;
			}
			if (i == nClient) nClient++;
		}
		for (i = 1; i < nClient; i++) {
			if (FD_ISSET(c[i], &fdread)) {
				len = recv(c[i], buf, 1024, 0);
				if (len > 0) {
					buf[len] = 0;
					printf("Client %d: %s\n", i, buf);
					sprintf(msg, "Client %d: %s\n", i, buf);
					for (int k = 1; k < nClient; k++) {
						if (k != i && c[k] != 0)
							send(c[k], msg, strlen(msg), 0);
					}
				}
				else {
					closesocket(c[i]);
					c[i] = 0;
					printf("Client %d ngat ket noi\n", i);
				}

			}
		}
	}

	closesocket(s);
	WSACleanup();

	getch();
	return 0;
}

