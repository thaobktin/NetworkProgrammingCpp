/*

  Author :- Nish [BusterBoy]
  EMail :- nishinapp@yahoo.com
  WWW :- http://www.busterboy.org

  */
#include "stdafx.h"
#include "SimpleTcpClient.h"
#include "SimpleTcpClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleTcpClientDlg dialog

CSimpleTcpClientDlg::CSimpleTcpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleTcpClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimpleTcpClientDlg)
	m_url = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleTcpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleTcpClientDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_url);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimpleTcpClientDlg, CDialog)
	//{{AFX_MSG_MAP(CSimpleTcpClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleTcpClientDlg message handlers

BOOL CSimpleTcpClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	m_url="http://www.codeproject.com/info/stuff/codeproject_w2k_bg.gif";
	UpdateData(false);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSimpleTcpClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSimpleTcpClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimpleTcpClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CSimpleTcpClientDlg::ParseURL(CString m_url, CString &server, CString &filepath, CString &filename)
{
	int n;
	CString url=m_url;
	if(url.Left(7)=="http://")
		url=url.Mid(7);
	n=url.Find('/');
	server=url.Left(n);
	filepath=url.Mid(n);
	n=filepath.ReverseFind('/');
	filename=filepath.Right(filepath.GetLength()-(n+1));

}

void CSimpleTcpClientDlg::DownloadFile()
{
	char buff[512];
	CString s;
	WSADATA wsaData;
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	CString servername; 
	CString filepath;
	CString filename;	
	ParseURL(m_url,servername,filepath,filename);
	int wsaret=WSAStartup(0x101,&wsaData);
	if(wsaret)	
		return;
	s.Format("Initialized WinSock");
	m_list.AddString(s);
	SOCKET conn;
	conn=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(conn==INVALID_SOCKET)
		return;
	s.Format("SOCKET created");
	m_list.AddString(s);
	if(inet_addr(servername)==INADDR_NONE)
	{
		hp=gethostbyname(servername);
	}
	else
	{
		addr=inet_addr(servername);
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	}
	if(hp==NULL)
	{
		closesocket(conn);
		return;
	}
	s.Format("hostname/ipaddress resolved");
	m_list.AddString(s);
	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(80);
	if(connect(conn,(struct sockaddr*)&server,sizeof(server)))
	{
		closesocket(conn);
		return;	
	}
	s.Format("Connected to server :- %s",servername);
	m_list.AddString(s);
	sprintf(buff,"GET %s\r\n\r\n",filepath);
	send(conn,buff,strlen(buff),0);
	s.Format("sending command :- GET %s to server",filepath);
	m_list.AddString(s);
	CFile f;
	int y;
	CString fname="c:\\";
	fname+=filename;
	f.Open(fname,CFile::modeCreate | CFile::modeWrite);
	s.Format("starting to receive file");
	m_list.AddString(s);
	while(y=recv(conn,buff,512,0))
	{
		f.Write(buff,y);
	}
	f.Close();
	s.Format("File downloaded and saved :- %s",fname);
	m_list.AddString(s);
	closesocket(conn);
	s.Format("SOCKET closed");
	m_list.AddString(s);
	WSACleanup();
	s.Format("De-Initialized WinSock");
	m_list.AddString(s);	

}

void CSimpleTcpClientDlg::OnOK() 
{	
	m_list.ResetContent();
	UpdateData(true);
	AfxBeginThread(StartDownload,this);
}


UINT CSimpleTcpClientDlg::StartDownload(LPVOID pParam )
{
	CSimpleTcpClientDlg* pDlg=(CSimpleTcpClientDlg*)pParam;
	pDlg->DownloadFile();
	return 0;
}
