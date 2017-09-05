// CSocketServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSocketServer.h"
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

CSocket	s, c;

DWORD	WINAPI	ReceiverThread(LPVOID lpParam)
{
	char	buffer[1025];
	int		len;
	CSocket c;
	c.Attach((SOCKET)lpParam);
	while (1)
	{
		len = c.Receive(buffer, 1024, 0);
		if (len > 0)
		{
			buffer[len] = 0;
			printf("Client:%s", buffer);
		}
		else
			break;
	};
	c.Close();
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			AfxSocketInit();
			s.Create(8888);
			s.Listen();
			printf("Dang doi ket noi o cong 8888...");
			s.Accept(c);
			printf("\nCo ket noi moi !");
			CreateThread(0, 0, ReceiverThread, (LPVOID)c.m_hSocket, 0, 0);
			//c.Detach();
			char	szXau[1025];
			int		len;
			while (1){
				printf("Nhap vo mot xau:");
				gets(szXau);
				c.Send(szXau, strlen(szXau));
			};
			c.Close();
			s.Close();
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
