// UDProcsCommDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDProcsComm.h"
#include "UDProcsCommDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CUDProcsCommDlg 对话框




CUDProcsCommDlg::CUDProcsCommDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUDProcsCommDlg::IDD, pParent)
	, str(_T(""))
	, LocalPort(_T(""))
	, DestPort(_T(""))
{
//ADD
	str = _T("");
	m_sport = 0;
	m_dport = 0;
//ADD
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//ADD
	IsTrue = FALSE;
	Client = INVALID_SOCKET;
//ADD
}

void CUDProcsCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Text(pDX, IDC_EDIT1, str);
	DDX_Control(pDX, IDC_IPADDRESS2, IPLocal);
	DDX_Text(pDX, IDC_EDIT2, LocalPort);
	DDX_Control(pDX, IDC_IPADDRESS1, IPDest);
	DDX_Text(pDX, IDC_EDIT3, DestPort);
	DDX_Control(pDX, IDC_EDIT2, PortLocal);
	DDX_Control(pDX, IDC_EDIT3, PortDest);
	DDX_Control(pDX, IDC_EDIT1, m_EditWords);
	DDX_Control(pDX, IDOK, m_Start);
	DDX_Control(pDX, IDC_BUTTON1, m_Stop);
	DDX_Control(pDX, IDC_BUTTON3, m_Send);
	DDX_Control(pDX, IDCANCEL, m_Exit);
}

BEGIN_MESSAGE_MAP(CUDProcsCommDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CUDProcsCommDlg::OnStop)
	ON_BN_CLICKED(IDC_BUTTON3, &CUDProcsCommDlg::OnSend)
//ADD
	ON_MESSAGE(WM_CLIENT_READCLOSE,OnReadClose)
//ADD
ON_BN_CLICKED(IDC_BUTTON2, &CUDProcsCommDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUDProcsCommDlg 消息处理程序

BOOL CUDProcsCommDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
//ADD
	IPLocal.SetFocus();
	list.EnableWindow(false);
	m_Stop.EnableWindow(false);
	IPDest.EnableWindow(false);
	PortDest.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
//ADD

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUDProcsCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUDProcsCommDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUDProcsCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUDProcsCommDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	UpdateData();
	if(IPLocal.IsBlank())
	{
		AfxMessageBox("请设置IP地址!");
		return;	
	}
	if(LocalPort.IsEmpty())
	{
		AfxMessageBox("请设置端口号!");
		return;
	}
	//初始化与绑定
    WSADATA wsaData;
    int iErrorCode;
    if (WSAStartup(MAKEWORD(2,1),&wsaData)) //调用Windows Sockets DLL
	{ 
         list.AddString("Winsock无法初始化!");
         WSACleanup();
         return;
	}

	list.AddString("开始创建Socket…");

	ServerSocket = socket(PF_INET,SOCK_DGRAM,0);    //创建本机进程的Socket，类型为SOCK_DGRAM，无连接的通信

    if(ServerSocket == INVALID_SOCKET)
	{
         list.AddString("创建socket失败!");
         return;
	}

	//获取本机进程的IP和端口
	BYTE nFild[4];
	CString sIP;
	IPLocal.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

    m_sockServerAddr.sin_family = AF_INET;
    m_sockServerAddr.sin_addr.s_addr = inet_addr(sIP); 
    m_sockServerAddr.sin_port = htons(atoi(LocalPort));

	socklen = sizeof(m_sockServerAddr);

    if (bind(ServerSocket,(LPSOCKADDR)&m_sockServerAddr,sizeof(m_sockServerAddr)) == SOCKET_ERROR) //与设置的端口绑定
    {
	    list.AddString("绑定失败!");
        return;
	}
	iErrorCode = WSAAsyncSelect(ServerSocket,m_hWnd,WM_CLIENT_READCLOSE,FD_READ);

    // 产生相应传递给窗口的消息为WM_SERVER_ACCEPT ，这是自定义消息

    if (iErrorCode == SOCKET_ERROR) 
	{
         list.AddString("WSAAsyncSelect设定失败!——用于连接请求的消息");
         return;
	}


 	list.AddString("本机进程启动成功!");
	list.AddString("地址 " + sIP + "  端口 " + LocalPort);
	this->SetWindowTextA("本机应用进程（" + sIP + ":" + LocalPort + "）-UDProcsComm");

	//界面
    IPLocal.EnableWindow(false);
	PortLocal.EnableWindow(false);
	m_Start.EnableWindow(false);
	m_Stop.EnableWindow(true);
	IPDest.EnableWindow(true);
	IPDest.SetFocus();
	PortDest.EnableWindow(true);
	m_EditWords.EnableWindow(true);
	m_Send.EnableWindow(true);
	list.EnableWindow(true);
	m_Exit.EnableWindow(false);
	//界面
    return; 
//ADD

	CDialog::OnOK();
}

void CUDProcsCommDlg::OnStop()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	//当程序停止运行时，把SOCKET清空
	list.AddString("正在关闭Socket…");
	closesocket(ServerSocket);
	WSACleanup();
	list.AddString("本机进程停止运行!");

	//界面
    IPLocal.EnableWindow(true);
	PortLocal.EnableWindow(true);
	m_Start.EnableWindow(true);
	m_Stop.EnableWindow(false);
	list.EnableWindow(false);
	IPLocal.SetFocus();

	IPDest.EnableWindow(false);
	PortDest.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
	m_Exit.EnableWindow(true);
	//界面

//ADD
}

void CUDProcsCommDlg::OnSend()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	//发送数据
	UpdateData();
	if(IPDest.IsBlank())
	{
		AfxMessageBox("请指定目标进程所在主机的IP地址!");
		return;	
	}
	if(DestPort.IsEmpty())
	{
		AfxMessageBox("请指定目标进程的端口号!");
		return;
	}
	//获取目标进程的IP和端口
	BYTE nFild[4];
	CString sIP;
	IPDest.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	m_sockAddrto.sin_family = AF_INET;
    m_sockAddrto.sin_addr.s_addr = inet_addr(sIP); 
    m_sockAddrto.sin_port = htons(atoi(DestPort));
	if(str.IsEmpty())
	{
	    AfxMessageBox("发送的消息不能为空!");
		return;
	}
	strcpy(msg.msg,(LPCTSTR)str);
	msg.i = 0;
	if(sendto(ServerSocket,(char *)&msg,sizeof(msg),0,(LPSOCKADDR)&m_sockAddrto,sizeof(m_sockAddrto)) == SOCKET_ERROR)
	{
		list.AddString("发送数据失败!");
	};
	str.Empty();
	UpdateData(FALSE);
//ADD
}

//ADD
LRESULT CUDProcsCommDlg::OnReadClose(WPARAM wParam,LPARAM lParam)
{
	//自定义的关闭与缓冲区有消息
	CString str;
	switch (WSAGETSELECTEVENT(lParam))
	{
	    case FD_READ:
		if(recvfrom(ServerSocket,(char *)&msg,sizeof(msg),0,(LPSOCKADDR)&m_sockServerAddr,(int *)&socklen) == SOCKET_ERROR)		
		{
			list.AddString("发送失败!对方主机或应用进程没有启动");
			return 0;
		}
		str.Format("%s",msg.msg);
		list.AddString(str);
		break;
	}
	return 0L;
}
//ADD

void CUDProcsCommDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
//ADD
}
