
// WonderwomanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Wonderwoman.h"
#include "WonderwomanDlg.h"
#include "afxdialogex.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//int ret = -1;

#define WM_SOCKET WM_USER+1
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


// CWonderwomanDlg dialog




CWonderwomanDlg::CWonderwomanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWonderwomanDlg::IDD, pParent)
	, chatxt(_T(""))
	, ip(_T(""))
	, port(_T(""))
	, nickname(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWonderwomanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CHATBOX, chatxt);
	DDX_Text(pDX, IDC_PI, ip);
	DDX_Text(pDX, IDC_EDIT3, port);
	DDX_Text(pDX, IDC_EDIT4, nickname);
	DDX_Control(pDX, IDC_NOC, Cbut);
	DDX_Control(pDX, IDC_HIS, History);
}

BEGIN_MESSAGE_MAP(CWonderwomanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_EN_CHANGE(IDC_EDIT2, &CWonderwomanDlg::OnEnChangeEdit2)
	//ON_EN_CHANGE(IDC_EDIT4, &CWonderwomanDlg::OnEnChangeEdit4)
	//ON_LBN_SELCHANGE(IDC_LIST2, &CWonderwomanDlg::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_DNES, &CWonderwomanDlg::OnBnClickedDnes)
	ON_EN_CHANGE(IDC_CHATBOX, &CWonderwomanDlg::OnEnChangeChatbox)
	ON_LBN_SELCHANGE(IDC_HIS, &CWonderwomanDlg::OnLbnSelchangeHis)
	ON_BN_CLICKED(IDC_NOC, &CWonderwomanDlg::OnBnClickedNoc)
	ON_BN_CLICKED(IDC_COL, &CWonderwomanDlg::OnBnClickedCol)
END_MESSAGE_MAP()


// CWonderwomanDlg message handlers

BOOL CWonderwomanDlg::OnInitDialog()
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
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2,2);
	WSAStartup(wVersion,&wsaData);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWonderwomanDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWonderwomanDlg::OnPaint()
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
HCURSOR CWonderwomanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWonderwomanDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CWonderwomanDlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CWonderwomanDlg::OnLbnSelchangeList2()
{
	// TODO: Add your control notification handler code here
}


void CWonderwomanDlg::OnBnClickedDnes()
{
	// TODO: Add your control notification handler code here
	UpdateData (true);
	send(client,(char*)chatxt.GetBuffer(),chatxt.GetLength()*2,0);
	History.AddString(chatxt);
}

LRESULT CWonderwomanDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	SOCKADDR_IN	serverAddr;
	int			serverAddrLen = sizeof(serverAddr);
	wchar_t		szMsg[1024];
	int			len;
	wchar_t		szThongbao[1024];
	switch (message)
	{
		case WM_SOCKET:
			if (WSAGETSELECTERROR(lParam))
		{
			wsprintf(szMsg,L"Kết nối tới server thất bại!");
			MessageBox(szMsg,L"Lỗi !",MB_ICONERROR);
			Cbut.SetWindowText(_T("Kết nối"));
			closesocket(client);
			UpdateData(false);
			ret = -1;
			break;
		}
		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_READ:
			len = recv(wParam,(char*)szMsg,2048,0);
			if (len > 0)
			{
				szMsg[len/2] = 0;
				// In ra cua so History
				wsprintf(szThongbao,L"%s",szMsg);
				History.AddString(szThongbao);
			};
			break;
		case FD_WRITE:
			break;
		case FD_CLOSE:
			wsprintf(szMsg,L"Kết nối tới server bị ngắt!");
			MessageBox(szMsg,L"Lỗi !",MB_ICONERROR);
			Cbut.SetWindowText(_T("Kết nối"));
			closesocket(client);
			UpdateData(false);
			ret = -1;
			break;

		}






	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CWonderwomanDlg::OnEnChangeChatbox()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO:  Add your control notification handler code here
}


void CWonderwomanDlg::OnLbnSelchangeHis()
{
	// TODO: Add your control notification handler code here
}


void CWonderwomanDlg::OnBnClickedNoc()
{
	// TODO: Add your control notification handler code here
	//SOCKET client;
	if (ret != 0)
	{
		UpdateData(true);
		char tport[1024];
		char tip[1024];
		WideCharToMultiByte(CP_ACP,0,ip,ip.GetLength(),tip,1024,0,0);
		tip[ip.GetLength()]=0;
		WideCharToMultiByte(CP_ACP,0,port,port.GetLength(),tport,1024,0,0);
		tport[port.GetLength()]=0;
		client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		SOCKADDR_IN serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(atoi(tport));
		serverAddr.sin_addr.s_addr = inet_addr(tip);
		WSAAsyncSelect(client,this->m_hWnd,WM_SOCKET,FD_READ|FD_CONNECT|FD_CLOSE);
		ret = connect(client,(sockaddr*)&serverAddr,sizeof(serverAddr));
		//if (ret == 0) Cbut.SetWindowText(_T("Ngắt"));
		ret = 0;
		Cbut.SetWindowText(_T("Ngắt"));
	}
	else {
		Cbut.SetWindowText(_T("Kết nối"));
		closesocket(client);
		UpdateData(false);
		ret = -1;
	}
}


void CWonderwomanDlg::OnBnClickedCol()
{
	// TODO: Add your control notification handler code here
	wchar_t* header = L">";
	UpdateData (true);
	send(client,(char*)header,2,0);
	send(client,(char*)nickname.GetBuffer(),nickname.GetLength()*2,0);
}
