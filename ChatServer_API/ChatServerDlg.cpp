// ChatServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"

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


// CChatServerDlg 对话框




CChatServerDlg::CChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatServerDlg::IDD, pParent)
	, sPort(_T(""))
	, m_sWords(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
	DDX_Control(pDX, IDC_EDIT1, ServerPort);
	DDX_Text(pDX, IDC_EDIT1, sPort);
	DDX_Control(pDX, IDC_LIST1, m_ListWords);
	DDX_Control(pDX, IDC_EDIT2, m_EditWords);
	DDX_Text(pDX, IDC_EDIT2, m_sWords);
	DDX_Control(pDX, IDC_BUTTON2, m_ButtonListen);
	DDX_Control(pDX, IDC_BUTTON3, m_ButtonStopListen);
	DDX_Control(pDX, IDC_BUTTON4, m_ButtonDisconnect);
	DDX_Control(pDX, IDC_BUTTON5, m_ButtonClear);
	DDX_Control(pDX, IDC_BUTTON6, m_ButtonSend);
	DDX_Control(pDX, IDCANCEL, m_ButtonExit);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CChatServerDlg::OnListen)
	ON_BN_CLICKED(IDC_BUTTON6, &CChatServerDlg::OnSend)
	ON_BN_CLICKED(IDC_BUTTON3, &CChatServerDlg::OnStopListen)
	ON_BN_CLICKED(IDC_BUTTON4, &CChatServerDlg::OnDisconnect)
	ON_BN_CLICKED(IDC_BUTTON5, &CChatServerDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CChatServerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CChatServerDlg 消息处理程序

BOOL CChatServerDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
//ADD
	//界面初始化
	m_ButtonStopListen.EnableWindow(false);
	m_ButtonDisconnect.EnableWindow(false);
	m_ButtonClear.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	//界面初始化
//ADD

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatServerDlg::OnPaint()
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
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatServerDlg::OnListen()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	WSADATA wsd;
	WSAStartup(MAKEWORD(2,2),&wsd);
	//创建套接字
	m_server = socket(AF_INET,SOCK_STREAM,0);
	//将网络中的事件关联到窗口的消息函数中
	WSAAsyncSelect(m_server,m_hWnd,20000,FD_ACCEPT);
	m_client = 0;
	//监听开始，服务器等待连接请求的到来
	BYTE nFild[4];
	CString sIP;
	UpdateData();
	if(ServerIP.IsBlank())
	{
		AfxMessageBox("请设置IP地址!");
		return;	
	}
	if(sPort.IsEmpty())
	{
		AfxMessageBox("请设置监听端口!");
		return;
	}
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	//服务器端地址
	sockaddr_in serveraddr;

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.S_un.S_addr  = inet_addr(sIP);
	serveraddr.sin_port = htons(atoi(sPort));

	//绑定地址
	if (bind(m_server,(sockaddr*)&serveraddr,sizeof(serveraddr)))
	{
		MessageBox("绑定地址失败.");
		return;
	}
	//开始监听
	listen(m_server,5);
	m_ListWords.AddString("监听开始：");
	m_ListWords.AddString("地址 " + sIP + "  端口 " + sPort);
	m_ListWords.AddString("等待客户端连接……");

	//界面完善
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
	ServerIP.EnableWindow(false);
	ServerPort.EnableWindow(false);
	m_ButtonListen.EnableWindow(false);
	m_ButtonStopListen.EnableWindow();
	m_ButtonClear.EnableWindow();
	m_ButtonExit.EnableWindow(false);
	//界面完善
//ADD
}

//ADD
void CChatServerDlg::HandleData()
{	
	sockaddr_in serveraddr;
	int len = sizeof(serveraddr);
	m_client = accept(m_server,(struct sockaddr*)&serveraddr,&len);
	WSAAsyncSelect(m_client,m_hWnd,30000,FD_READ|FD_CLOSE);
	m_ListWords.AddString("接受了一个客户端的连接请求");
	m_ListWords.SetTopIndex(m_ListWords.GetCount() - 1);

		//界面完善
	    m_ButtonDisconnect.EnableWindow();
	    m_EditWords.EnableWindow();
	    m_ButtonSend.EnableWindow();
	    //界面完善
}

void CChatServerDlg::ReceiveData()
{
	//接收客户端的数据
	char buffer[1024];
	int num = recv(m_client,buffer,1024,0);
	buffer[num] = 0;
    CString sTemp;
	sTemp.Format("收到：%s",buffer);
	m_ListWords.AddString(sTemp);//显示信息
	m_ListWords.SetTopIndex(m_ListWords.GetCount() - 1);
	WSAAsyncSelect(m_client,m_hWnd,30000,FD_READ|FD_CLOSE);
}

void CChatServerDlg::CloseSock()
{
	//关闭与客户端的通信信道
	m_ListWords.AddString("客户端断开连接");
	m_ListWords.SetTopIndex(m_ListWords.GetCount() - 1);
	closesocket(m_client);//关闭与客户端通信的Socket
	WSAAsyncSelect(m_server,m_hWnd,20000,FD_ACCEPT);

	//界面完善
	m_ButtonDisconnect.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	//界面完善

}
//ADD

BOOL CChatServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	if (pMsg->message == 20000)
	{
		this->HandleData();
	}
	else if(pMsg->message == 30000)
	{
		switch(pMsg->lParam)
		{
			case FD_READ:
				this->ReceiveData();
			    break;
			case FD_CLOSE:
				this->CloseSock();
				break;
		}
	}
	else
//ADD
	return CDialog::PreTranslateMessage(pMsg);
}

void CChatServerDlg::OnSend()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	//向服务器发信息
	UpdateData();
	if(m_sWords.IsEmpty())
	{
	    AfxMessageBox("发送的消息不能为空!");
		return;
	}
	//开始发送数据
	int i = send(m_client,m_sWords.GetBuffer(0),m_sWords.GetLength(),0);
	m_ListWords.AddString("发送：" + m_sWords);
	m_ListWords.SetTopIndex(m_ListWords.GetCount() - 1);
//ADD
}

void CChatServerDlg::OnStopListen()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	//停止监听
    closesocket(m_server);
	m_ListWords.AddString("停止监听");

	//界面完善
	m_ListWords.SetTopIndex(m_ListWords.GetCount() - 1);
	ServerIP.EnableWindow();
	ServerPort.EnableWindow();
	m_ButtonListen.EnableWindow();
	m_ButtonStopListen.EnableWindow(false);
	m_ButtonExit.EnableWindow();
	//界面完善
//ADD
}

void CChatServerDlg::OnDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	closesocket(m_client);
	m_ListWords.AddString("与客户端断开");

	//界面完善
	m_ListWords.SetTopIndex(m_ListWords.GetCount() - 1);
	m_ButtonDisconnect.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	//界面完善

//ADD
}

void CChatServerDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	m_ListWords.ResetContent();
//ADD
}

void CChatServerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();//显示“关于”对话框
//ADD
}
