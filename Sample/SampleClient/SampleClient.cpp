// SampleClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA DATA;
	WSAStartup(MAKEWORD(2, 2), &DATA);

	SOCKET c = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN caddr;
	caddr.sin_family = AF_INET;
	caddr.sin_port = htons(80);
	caddr.sin_addr.S_un.S_addr = inet_addr("111.65.248.132");
	int x = connect(c, (sockaddr*)&caddr, sizeof(caddr));
	char* request = "GET http://vnexpress.net/photo/thoi-su/nguoi-phu-nu-bi-hat-khoi-cau-khi-oto-tong-hang-loat-xe-may-3276494.html HTTP/1.1\r";
	send(c, request, strlen(request) + 1, 0);

	char tmp[100];		//Bo dem nhan tam thoi - 100 Byte
	int total = 0;		//Tong so byte da nhan
	char* buf = NULL;	//Bo dem nhan cuoi cung

	int r = recv(c, tmp, 100, 0);	//Nhan tam 100 Byte
	while (r > 0)					//Neu du lieu van con
	{
		//Mo rong bo dem them r byte 
		buf = (char*)realloc(buf, total + r); 
		//Bo sung du lieu vua nhan vao cuoi bo dem
		memcpy(buf + total, tmp, r);
		//Tang tong so byte da nhan
		total += r;
		//Tiep tuc nhan tam 100 Byte nua
		r = recv(c, tmp, 100, 0);
	}
	printf("%s", buf);

	free(buf);
	closesocket(c);
	WSACleanup();
	return 0;
}
