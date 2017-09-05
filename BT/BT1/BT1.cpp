// BT1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <conio.h>
#include <stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA DATA;
	int err = WSAStartup(MAKEWORD(2, 2), &DATA);
	char* ipstr = (char*)calloc(1024, sizeof(char));
	int port = 0;
	if (argc >= 3)
	{
		//Ham duoi chuyen xau unicode argv[1] thanh xau ascii ipstr
		wcstombs(ipstr, argv[1], 1024);
		//Ham duoi chuyen xau unicode argv[2] thanh so nguyen port
		port = _wtoi(argv[2]);
		SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Tao socket kieu TCP
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons((short)port);
		addr.sin_addr.S_un.S_addr = inet_addr(ipstr);
		connect(s, (sockaddr*)&addr, sizeof(addr));
		//BAT DAU LAP LAY DU LIEU VA GUI DI
		char* datastr = (char*)calloc(1024, 1); //Bo dem chua du lieu
		do
		{
			fflush(stdin); //Xoa dem ban phim
			gets(datastr); //Doc du lieu tu ban phim
			send(s, datastr, strlen(datastr), 0); //Gui len server
		} while (strlen(datastr) > 0); //Nhap xau rong de thoat		
		free(datastr);
	}
	else
		printf("KHONG DU THAM SO\n");

	free(ipstr);
	return 0;
}

