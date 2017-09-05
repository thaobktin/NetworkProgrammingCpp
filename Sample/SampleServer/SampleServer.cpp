// SampleServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA DATA;
	//Khoi tao thu vien
	WSAStartup(MAKEWORD(2, 2), &DATA); 
	//Tao socket theo giao thuc TCP
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//Khai bao va dien cac gia tri khoi tao dia chi
	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET; //IPV4
	saddr.sin_port = htons(5000); //CONG 5000
	saddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //Ko can biet dia chi
	//Gan socket s vao dia chi vua khai bao o tren
	bind(	s,					//SOCKET
			(sockaddr*)&saddr,	//Con tro den cau truc dia chi
			sizeof(saddr)		//So byte cua cau truc dia chi
		);
	listen(	s,		//SOCKET
			5);		//>0 la duoc
	SOCKADDR_IN caddr;
	int clen = sizeof(caddr);
	SOCKET c =							//Kenh trao doi du lieu
			accept( s,					//Kenh phuc vu ket noi
					(sockaddr*)&caddr,	//Thong tin may xin ket noi 
					&clen				//So byte trong cau truc caddr	
				  );
	//In dia chi IP ra man hinh
	printf("%s\n", inet_ntoa(caddr.sin_addr));

	//Bo dem nhan va gui du lieu
	char* str = "May la ai?";
	char buf[1024];

	//Gui du lieu
	send(c, str, strlen(str), 0);

	//Xoa sach bo dem de chuan bi nhan
	memset(buf, 0, sizeof(buf));

	//Nhan du lieu
	recv(c, buf, sizeof(buf), 0);

	//Dong kenh
	closesocket(c);
	closesocket(s);

	//Dong thu vien
	WSACleanup();

	return 0;
}

