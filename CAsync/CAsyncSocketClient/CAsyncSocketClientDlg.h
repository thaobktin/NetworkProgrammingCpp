
// CAsyncSocketClientDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CCAsyncSocketClientDlg dialog
class CCAsyncSocketClientDlg : public CDialogEx
{
// Construction
public:
	CCAsyncSocketClientDlg(CWnd* pParent = NULL);	// standard constructor
	void OnMyReceive(wchar_t * szMessage);
	void OnMyClose();
	CMySocket s;

// Dialog Data
	enum { IDD = IDD_CASYNCSOCKETCLIENT_DIALOG };

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
	CListBox m_lHistory;
	CString m_szText;
	afx_msg void OnBnClickedConnect();
	
	afx_msg void OnBnClickedSend();
};
