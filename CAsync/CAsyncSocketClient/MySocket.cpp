// MySocket.cpp : implementation file
//

#include "stdafx.h"
#include "MySocket.h"
#include "CAsyncSocketClient.h"
#include "CAsyncSocketClientDlg.h"
// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket member functions


void CMySocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	MessageBox(pWnd->m_hWnd, L"Thông báo", L"Kết nối thành công !",
		MB_ICONINFORMATION);
	

	CAsyncSocket::OnConnect(nErrorCode);
}


void CMySocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	((CCAsyncSocketClientDlg*)pWnd)->OnMyClose();
	CAsyncSocket::OnClose(nErrorCode);
}


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	wchar_t	szMessage[1025];
	int		len;
	len = Receive((char*)szMessage, 1024 * 2, 0);
	if (len > 0)
	{
		szMessage[len / 2] = 0;
		((CCAsyncSocketClientDlg*)pWnd)->OnMyReceive(szMessage);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
