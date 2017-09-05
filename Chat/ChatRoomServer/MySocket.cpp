// MySocket.cpp : implementation file
//

#include "stdafx.h"
#include "ChatRoomServer.h"
#include "MySocket.h"
#include "ChatRoomServerDlg.h"

void* CMySocket::m_pChatRoomDlg = NULL;
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
	CAsyncSocket::OnConnect(nErrorCode);
}


void CMySocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	CMySocket**& pClients = ((CChatRoomServerDlg*)m_pChatRoomDlg)->m_pClients;
	int nClients = ((CChatRoomServerDlg*)m_pChatRoomDlg)->m_nClients;
	pClients = (CMySocket**)realloc(pClients, (nClients + 1) * sizeof(CMySocket*));
	nClients += 1;
	((CChatRoomServerDlg*)m_pChatRoomDlg)->m_nClients += 1;	
	((CChatRoomServerDlg*)m_pChatRoomDlg)->m_nTotalClients += 1;
	pClients[nClients - 1] = new CMySocket();
	Accept(*pClients[nClients - 1]);

	((CChatRoomServerDlg*)m_pChatRoomDlg)->m_ctrlSend.EnableWindow(TRUE);

	CAsyncSocket::OnAccept(nErrorCode);
}


void CMySocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	((CChatRoomServerDlg*)m_pChatRoomDlg)->m_nTotalClients -= 1;
	if (((CChatRoomServerDlg*)m_pChatRoomDlg)->m_nTotalClients == 0)
	{
		((CChatRoomServerDlg*)m_pChatRoomDlg)->m_ctrlSend.EnableWindow(FALSE);
	}
	CAsyncSocket::OnClose(nErrorCode);
}


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	char* buffer = (char*)calloc(1024, 1);
	Receive(buffer, 1024);
	((CChatRoomServerDlg*)m_pChatRoomDlg)->m_strMessage += buffer;
	((CChatRoomServerDlg*)m_pChatRoomDlg)->m_strMessage += "\r\n";
	((CChatRoomServerDlg*)m_pChatRoomDlg)->UpdateData(FALSE);
	CAsyncSocket::OnReceive(nErrorCode);
}
