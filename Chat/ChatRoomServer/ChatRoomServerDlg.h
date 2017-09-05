
// ChatRoomServerDlg.h : header file
//

#pragma once
#include "MySocket.h"
#include "afxwin.h"

// CChatRoomServerDlg dialog
class CChatRoomServerDlg : public CDialogEx
{
public:
	CMySocket m_socket;
	CMySocket** m_pClients = NULL;
	int m_nClients = 0;
	int m_nTotalClients = 0;
// Construction
public:
	CChatRoomServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHATROOMSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonListen();
	CString m_strPort;
	afx_msg void OnClickedButtonSend();
	CString m_editSend;
	CButton m_ctrlListen;
//	CEdit m_ctrlSend;
	CButton m_ctrlSend;
	CString m_strMessage;
};
