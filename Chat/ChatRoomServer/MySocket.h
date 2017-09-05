#pragma once

// CMySocket command target

class CMySocket : public CAsyncSocket
{
public:
	static void* m_pChatRoomDlg;
	CMySocket();
	virtual ~CMySocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


