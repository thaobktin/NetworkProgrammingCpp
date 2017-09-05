// BT3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
SOCKET client[1024];
char* cname[1024];
int nc = 0;

DWORD WINAPI Send_Recv_Thread(LPVOID arg)
{
	int j = 0;
	SOCKET c = (SOCKET)arg;
	do
	{
		char* str = (char*)calloc(1024, 1);		//Cap phat bo nho de nhan du lieu
		recv(c, str, 1024, 0);					//Nhan du lieu tu client
		if (strstr(str, "client_id: ") == str)	//Kiem tra xem du lieu co phai dinh dang "client_id: xxxxx" khong
		{			
			for (j = 0; j < nc; j++)			//Neu dung thi tim vi tri cua kenh hien tai "c" trong mang client
			{
				if (client[j] == c)
					break;
			}
			//j la chi so cua kenh "c" trong mang client

			cname[j] = (char*)calloc(1024, 1); //Cap phat bo nho de chua ten cua kenh "c"
			strcpy(cname[j], str + strlen("client_id: ")); //Tach phan ten tu chuoi "client_id: xxxxx" vao luu vao cname[j]
			while (cname[j][strlen(cname[j]) - 1] == '\n') //Loai bo ky tu \n - xuong dong khoi ten
				cname[j][strlen(cname[j]) - 1] = '\0';
			strcat(cname[j], ": "); //Ghep them dau ": " vao ten
			break;
		}
		free(str);
	} while (0 == 0); //Lap khi nao du lieu nhan duoc con chua dung cu phap "client_id: xxxxx"

	int n = 0;
	do
	{
		char* str = (char*)calloc(1024, 1); //Cap phat bo nho de nhan du lieu
		n = recv(c, str, 1024, 0);			//Nhan du lieu
		if (n > 0)
		{ 
			for (int i = 0; i < nc; i++)	//Duyet tat ca cac kenh da ket noi
			{
				if (client[i] != c)			//Chon kenh khong phai la kenh hien tai
				{					
					char* tmp = (char*)calloc(1024, 1);	//Ghep them ten vao dau du lieu can gui di
					strcpy(tmp, cname[j]);
					tmp = strcat(tmp, str);
					send(client[i], tmp, n + strlen(tmp), 0); //Gui du lieu di
					free(tmp); //Giai phong bo nho tam thoi
				}
			}
		}
		free(str);
	} while (n > 0);

	closesocket(c);

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	short port = _wtoi(argv[1]);
	WSADATA DATA;
	WSAStartup(MAKEWORD(2, 2), &DATA);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bind(s, (sockaddr*)&addr, sizeof(addr));
	listen(s, 5);
	while (true)
	{
		SOCKADDR_IN caddr;
		int clen = sizeof(caddr);
		SOCKET c = accept(s, (sockaddr*)&caddr, &clen);
		client[nc] = c; //Luu socket client vao mang
		nc = nc + 1;	//Tang so luong client
		CreateThread(NULL, 0, Send_Recv_Thread, (LPVOID)c, 0, NULL);
	}

	return 0;
}

