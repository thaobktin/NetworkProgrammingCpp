// CSocketClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSocketClient.h"
#include <conio.h>
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

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
			CSocket	c;
			c.Create();
			if (c.Connect(L"vietnamnet.vn", 80) == FALSE)
			{
				printf("Khong ket noi duoc den server !");
				return 0;
			};
			char * request = "GET / HTTP/1.0\r\nHost:vietnamnet.vn\r\n\r\n";
			c.Send(request, strlen(request));
			char	buffer[65537];
			int		len = 0;
			len = c.Receive(buffer, 65536);
			buffer[len] = 0;
			printf("%s", buffer);
			c.Close();
			getch();

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
