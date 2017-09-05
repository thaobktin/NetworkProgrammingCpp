
// CAsyncSocketClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MySocket.h"
#include "CAsyncSocketClient.h"
#include "CAsyncSocketClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCAsyncSocketClientDlg dialog



CCAsyncSocketClientDlg::CCAsyncSocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCAsyncSocketClientDlg::IDD, pParent)
	, m_szText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCAsyncSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_lHistory);
	DDX_Text(pDX, IDC_TEXT, m_szText);
}

BEGIN_MESSAGE_MAP(CCAsyncSocketClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CCAsyncSocketClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_SEND, &CCAsyncSocketClientDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CCAsyncSocketClientDlg message handlers

BOOL CCAsyncSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	AfxSocketInit();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCAsyncSocketClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCAsyncSocketClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCAsyncSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CCAsyncSocketClientDlg::OnMyReceive(wchar_t * szMessage)
{
	m_lHistory.AddString(szMessage);
}

void CCAsyncSocketClientDlg::OnMyClose()
{
	MessageBox(L"Kết nối bị ngắt !",L"Lỗi", MB_ICONEXCLAMATION);
}

void CCAsyncSocketClientDlg::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here
	s.Create();
	s.pWnd = this;
	s.Connect(L"127.0.0.1", 8888);
}


void CCAsyncSocketClientDlg::OnBnClickedSend()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	s.Send((char*)m_szText.GetBuffer(), m_szText.GetLength() * 2, 0);
}
