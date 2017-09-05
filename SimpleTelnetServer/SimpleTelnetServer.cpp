// SimpleTelnetServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>

DWORD WINAPI ServingThread(LPVOID arg)
{
	SOCKET c = (SOCKET)arg;
	char* hello = "Please input your user and password: ";
	send(c, hello, strlen(hello) + 1, 0);
	while (0 == 0)
	{
		//Nhan du lieu tu client
		char* buff = (char*)calloc(1024, 1);
		int r = recv(c, buff, 1024, 0);
		//Tach du lieu dang "user password" thanh hai truong
		char* user = (char*)calloc(1024, 1);
		char* pass = (char*)calloc(1024, 1);
		sscanf(buff, "%s%s", user, pass);
		//Kiem tra xem user, pass co trong file ko
		FILE* f = fopen("c:\\temp\\database.txt","rt");
		bool logged = FALSE;
		while (!feof(f))
		{
			//Doc mot dong trong file va tach ra user, pass
			memset(buff, 0, 1024);
			fgets(buff, 1024, f);
			char* duser = (char*)calloc(1024, 1);
			char* dpass = (char*)calloc(1024, 1);
			sscanf(buff, "%s%s", duser, dpass);
			//So sanh user pass
			if (strcmp(user, duser) == 0 &&
				strcmp(pass, dpass) == 0)
			{
				logged = TRUE;
				break; //Thoat vong lap hoi user/pass
			}			
			free(duser); 
			free(dpass);
		}
		fclose(f);
		free(user);
		free(pass);
		if (logged == TRUE)
		{
			char* msg = "Please input your commands:\n";
			send(c, msg, strlen(msg) + 1, 0);
			//San sang nhan lenh tu client va thuc thi
			while (0 == 0)
			{
				memset(buff, 0, 1024);
				recv(c, buff, 1024, 0);
				//Loai cac ky tu dac biet o cuoi
				while (	buff[strlen(buff) - 1] == '\r' ||
						buff[strlen(buff) - 1] == '\n' ||
						buff[strlen(buff) - 1] == ' ' ||
						buff[strlen(buff) - 1] == '\t')
				{
					buff[strlen(buff) - 1] = '\0';
				}
				if (strcmp(buff, "exit") == 0)
				{
					break;
				}
				else
				{
					char* command = strcat(buff, "> c:\\temp\\out.txt");
					system(command);
					//Doc file out.txt de gui tra client
					FILE* f = fopen("c:\\temp\\out.txt","rt");
					while (!feof(f))
					{
						memset(buff, 0, 1024);
						fgets(buff, 1024, f); //Doc mot dong
						send(c, buff, strlen(buff) + 1, 0); //Gui di
					}
					fclose(f);
				}
			}
			free(buff);
			break;
		}
		else
		{
			char* err = "Invalid user/password";
			send(c, err, strlen(err) + 1, 0);
		}
	}

	char* bye = "Bye!\n";
	send(c, bye, strlen(bye) + 1, 0);

	closesocket(c);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 2)
	{
		printf("KHONG DU THAM SO");
	}
	else
	{
		WSADATA DATA;
		WSAStartup(MAKEWORD(2, 2), &DATA);
		SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		SOCKADDR_IN saddr;
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons((short)_wtoi(argv[1]));
		saddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		bind(s, (sockaddr*)&saddr, sizeof(saddr));
		listen(s, 10);

		while (0 == 0)
		{
			SOCKADDR_IN caddr;
			int clen = sizeof(caddr);
			SOCKET c = accept(s, (sockaddr*)&caddr, &clen);
			CreateThread(NULL,
				0,
				ServingThread, (LPVOID)c, 
				0, NULL);
		}

	}
	return 0;
}

