// BTH_Select.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
//So luong lon nhat co the xu ly voi mot thread
#define MAX_SOCKET 2
SOCKET* g_socket = NULL;
int g_num = 0;
int g_thread = 0; //So luong dang co

DWORD WINAPI SelectThread(LPVOID param)
{	
	int index = (int)param;

	fd_set fdread;
	while (0 == 0)
	{		
		FD_ZERO(&fdread);
		for (int i = 0; i < MAX_SOCKET; i++)
		{
			FD_SET(g_socket[i + index], &fdread);
		}		
		select(0, &fdread, NULL, NULL, NULL);

		for (int i = 0; i < MAX_SOCKET; i++)
		{			
			if (FD_ISSET(g_socket[i + index], &fdread))
			{
				char* buf = (char*)calloc(1024, 1);
				recv(g_socket[i + index], buf, 1024, 0);
				printf("%s\n", buf);
				free(buf);			
			}
		}		
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA DATA;
	WSAStartup(MAKEWORD(2, 2), &DATA);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN saddr;
	short port = 0;
	printf("Cong: ");
	scanf("%d", &port);
	saddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);	
	bind(s, (sockaddr*)&saddr, sizeof(saddr));
	listen(s, 5);
	fd_set fdread;

	while (0 == 0)
	{
		FD_ZERO(&fdread);
		FD_SET(s, &fdread);
		
		for (int i = g_thread * MAX_SOCKET; i < g_num; i++)
		{
			FD_SET(g_socket[i], &fdread);
		}
		select(0, &fdread, NULL, NULL, NULL);

		for (int i = g_thread * MAX_SOCKET; i < g_num; i++)
		{
			if (FD_ISSET(g_socket[i], &fdread))
			{
				//Co du lieu tren kenh "i"
				char* buf = (char*)calloc(1024, 1);
				recv(g_socket[i], buf, 1024, 0);
				printf("%s\n", buf);
				free(buf);
				buf = NULL;
			}
		}

		if (FD_ISSET(s, &fdread))
		{
			//Co su kien xay ra tren socket "s"
			SOCKADDR_IN caddr;
			int clen = sizeof(caddr);
			SOCKET c = accept(s, (sockaddr*)&caddr, &clen);			
			//Cap phat them mot bien SOCKET trong mang g_socket
			g_socket = (SOCKET*)realloc(g_socket, (g_num + 1) * sizeof(SOCKET));
			g_socket[g_num] = c;
			g_num += 1;
			if (g_num >= (g_thread + 1) * MAX_SOCKET)
			{
				CreateThread(NULL, 0, SelectThread, (LPVOID)(g_thread * MAX_SOCKET), 0, NULL);
				g_thread += 1;
			}			
		}
	}

	return 0;
}

