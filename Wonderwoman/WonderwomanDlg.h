
// WonderwomanDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CWonderwomanDlg dialog
class CWonderwomanDlg : public CDialogEx
{
// Construction
public:
	CWonderwomanDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WONDERWOMAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	SOCKET client;

// Implementation
protected:
	HICON m_hIcon;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedDnes();
	afx_msg void OnEnChangeChatbox();
	afx_msg void OnLbnSelchangeHis();
	afx_msg void OnBnClickedNoc();
	CString chatxt;
	CString ip;
	CString port;
	afx_msg void OnBnClickedCol();
	CString nickname;
	CButton Cbut;
	int ret;
	CListBox History;
};
