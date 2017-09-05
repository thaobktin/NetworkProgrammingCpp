#pragma once

// CMySocket command target

class CMySocket : public CAsyncSocket
{
public:
	CDialog * pWnd;
	CMySocket();
	virtual ~CMySocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


