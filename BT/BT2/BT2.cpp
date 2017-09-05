// BT2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <Windows.h>

char* fchao = NULL;
char* fout = NULL;
DWORD WINAPI Send_Recv_Thread(LPVOID arg);
HANDLE hLock = INVALID_HANDLE_VALUE;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc >= 4)
	{
		//Tao mot khoa chong xung dot FILE
		hLock = CreateEvent(NULL, TRUE, TRUE, NULL);
		SetEvent(hLock); //Mo khoa san

		short port = _wtoi(argv[1]);		//Doc gia tri PORT tu tham so dong lenh
		fchao = (char*)calloc(1024, 1);		//Cap phat bo nho cho bien fchao toi da 1024 ky tu ascii
		wcstombs(fchao, argv[2], 1024);		//Chuyen tu xau ky tu unicode sang xau ky tu ascii
		fout = (char*)calloc(1024, 1);		//Cap phat bo nho cho bien fout toi da 1024 ky tu ascii
		wcstombs(fout, argv[3], 1024);		//Chuyen tu xau unicode sang xau ascii
		WSADATA DATA;
		WSAStartup(MAKEWORD(2, 2), &DATA);
		SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//Tao socket
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
			SOCKET c = accept(s, (sockaddr*)&caddr, &clen);			//Chap nhan ket noi cua mot client nao do	
			CreateThread(NULL, 0, Send_Recv_Thread, (LPVOID)c, 0, NULL);	//Tao ra luong Send_Recv_Thread de gui nhan du lieu, chay song song voi luong hien tai
		}
	}
	else
		printf("KHONG DU THAM SO");
	return 0;
}

DWORD WINAPI Send_Recv_Thread(LPVOID arg)	//Luong gui nhan du lieu, chay song song voi luong chinh cua ham main
{
	SOCKET c = (SOCKET)arg;
	FILE* f = fopen(fchao, "r+t");			//Mo file chua noi dung chao, r+t = read o che do text
	while (feof(f) == FALSE)				//Khi nao file van con du lieu
	{
		char* str = (char*)calloc(1024, 1);	//Cap phat bo nho de chua du lieu doc duoc tu file
		fgets(str, 1024, f);				//Doc mot dong tu file, toi da 1024 ky tu ascii	
		send(c, str, strlen(str), 0);		//Gui du lieu vua doc duoc tu file cho client ket noi den server qua kenh socket "c"
		free(str);							//Giai phong bo nho du lieu
		str = NULL;
	}
	fclose(f);
	int n = 0;
	do
	{
		char* str = (char*)calloc(1024, 1);	//Cap phat bo nho de nhan du lieu
		n = recv(c, str, 1024, 0);			//Nhan du lieu
		if (n > 0)							//Neu so byte nhan duoc > 0
		{
			//Doi khoa mo ra
			WaitForSingleObject(hLock, INFINITE);	
			//Chiem dung va khoa lai
			ResetEvent(hLock); 
			f = fopen(fout, "a+t");	//Mo file de ghi du lieu ra or dang append (ghi noi vao cuoi) va text
			fputs(str, f);			//Ghi vao cuoi file
			fclose(f);				//Dong file lai
			//Mo lai khoa
			SetEvent(hLock);
		}
		free(str);
	} while (n > 0);

	closesocket(c);

	return 0;
}

