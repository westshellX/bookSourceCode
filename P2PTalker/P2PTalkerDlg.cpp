// P2PTalkerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "P2PTalker.h"
#include "P2PTalkerDlg.h"

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


// CP2PTalkerDlg 对话框




CP2PTalkerDlg::CP2PTalkerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CP2PTalkerDlg::IDD, pParent)
	, sevrPort(_T(""))
	, locaPort(_T(""))
	, nickname(_T(""))
	, strMessage(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CP2PTalkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, SevrIP);
	DDX_Text(pDX, IDC_EDIT1, sevrPort);
	DDX_Control(pDX, IDC_IPADDRESS2, LocaIP);
	DDX_Text(pDX, IDC_EDIT2, locaPort);
	DDX_Text(pDX, IDC_EDIT5, nickname);
	DDX_Control(pDX, IDC_EDIT3, m_MessageList);
	DDX_Control(pDX, IDC_LIST1, m_UserList);
	DDX_Text(pDX, IDC_EDIT4, strMessage);
	DDX_Control(pDX, IDC_EDIT4, m_EditWords);
	DDX_Control(pDX, IDOK, m_Start);
	DDX_Control(pDX, IDC_BUTTON3, m_Stop);
	DDX_Control(pDX, IDC_EDIT2, m_LcaPrt);
	DDX_Control(pDX, IDC_BUTTON2, m_Login);
	DDX_Control(pDX, IDC_BUTTON1, m_Logout);
	DDX_Control(pDX, IDC_EDIT1, m_SvrPrt);
	DDX_Control(pDX, IDC_EDIT5, m_nicnam);
	DDX_Control(pDX, IDC_BUTTON5, m_Send);
	DDX_Control(pDX, IDCANCEL, m_exit);
}

BEGIN_MESSAGE_MAP(CP2PTalkerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &CP2PTalkerDlg::OnStop)
	ON_BN_CLICKED(IDC_BUTTON2, &CP2PTalkerDlg::OnLogin)
//ADD
	ON_MESSAGE(WM_CLIENT_READCLOSE,OnReadMsg)                //一定要有这个消息映射，否则无法接收信息
//ADD
ON_BN_CLICKED(IDC_BUTTON1, &CP2PTalkerDlg::OnLogout)
ON_BN_CLICKED(IDC_BUTTON5, &CP2PTalkerDlg::OnSend)
ON_BN_CLICKED(IDC_BUTTON4, &CP2PTalkerDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CP2PTalkerDlg 消息处理程序

BOOL CP2PTalkerDlg::OnInitDialog()
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
	rstUsrCont = 0;
	onlUsrCont = 0;

	//界面
	m_Stop.EnableWindow(false);
	m_Login.EnableWindow(false);
	m_Logout.EnableWindow(false);
	SevrIP.EnableWindow(false);
	m_SvrPrt.EnableWindow(false);
	m_nicnam.EnableWindow(false);
	m_UserList.EnableWindow(false);
	m_MessageList.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
	//
//ADD

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CP2PTalkerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CP2PTalkerDlg::OnPaint()
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
HCURSOR CP2PTalkerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CP2PTalkerDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	//输入验证
	UpdateData();
	if(LocaIP.IsBlank())
	{
		AfxMessageBox("请设置本机IP地址!");
		return;	
	}
	if(locaPort.IsEmpty())
	{
		AfxMessageBox("请指定通信端口号!");
		return;
	}

	//初始化套接字与绑定
    WSADATA wsaData;
    int iErrorCode;
    if (WSAStartup(MAKEWORD(2,1),&wsaData))         //调用Windows Sockets DLL
	{
		m_MessageList.ReplaceSel("Winsock无法初始化!\r\n");
        WSACleanup();
        return;
	}
	m_MessageList.ReplaceSel("开始创建Socket…\r\n");
	SelfRcvSocket = socket(PF_INET,SOCK_DGRAM,0);    //创建本机进程的Socket，类型为SOCK_DGRAM，无连接的通信
    if(SelfRcvSocket == INVALID_SOCKET)
	{
		m_MessageList.ReplaceSel("创建socket失败!\r\n");
        return;
	}

	//获取本机进程的IP和端口
	BYTE nFild[4];
	CString sIP;
	LocaIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
    m_sockSelfRcvAddr.sin_family = AF_INET;
    m_sockSelfRcvAddr.sin_addr.S_un.S_addr = inet_addr(sIP); 
    m_sockSelfRcvAddr.sin_port = htons(atoi(locaPort));

	//将套接字与本机进程绑定
    if(bind(SelfRcvSocket,(LPSOCKADDR)&m_sockSelfRcvAddr,sizeof(m_sockSelfRcvAddr)) == SOCKET_ERROR)
    {
		m_MessageList.ReplaceSel("绑定失败!\r\n");
        return;
	}
	iErrorCode = WSAAsyncSelect(SelfRcvSocket,m_hWnd,WM_CLIENT_READCLOSE,FD_READ);
    if (iErrorCode == SOCKET_ERROR) 
	{
		m_MessageList.ReplaceSel("WSAAsyncSelect设定失败!——用于连接请求的消息\r\n");
        return;
	}
 	m_MessageList.ReplaceSel("本机进程启动成功!\r\n");
	m_MessageList.ReplaceSel("地址 " + sIP + "  端口 " + locaPort);
	this->SetWindowTextA("本机进程（" + sIP + ":" + locaPort + "）正在运行… - ptopTalker");
	
	//界面
	m_Start.EnableWindow(false);
	m_Stop.EnableWindow(true);
	LocaIP.EnableWindow(false);
	m_LcaPrt.EnableWindow(false);
	m_Login.EnableWindow(true);
	SevrIP.EnableWindow(true);
	m_SvrPrt.EnableWindow(true);
	m_nicnam.EnableWindow(true);
	m_MessageList.EnableWindow(true);
	m_exit.EnableWindow(false);
	m_nicnam.SetFocus();
	//
    return; 
//ADD

	CDialog::OnOK();
}

void CP2PTalkerDlg::OnStop()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	//当程序停止运行时，把SOCKET清空
	m_MessageList.ReplaceSel("\r\n正在关闭Socket…\r\n");
	closesocket(SelfRcvSocket);
	WSACleanup();
	m_MessageList.ReplaceSel("本机进程停止运行!\r\n");
	this->SetWindowTextA("ptopTalker");

	//界面
	m_Start.EnableWindow(true);
	m_Stop.EnableWindow(false);
	LocaIP.EnableWindow(true);
	m_LcaPrt.EnableWindow(true);
	m_exit.EnableWindow(true);
	m_Login.EnableWindow(false);
	m_nicnam.EnableWindow(false);
	SevrIP.EnableWindow(false);
	m_SvrPrt.EnableWindow(false);
	LocaIP.SetFocus();
	//
//ADD
}

void CP2PTalkerDlg::OnLogin()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	//输入验证
	UpdateData();
	if(nickname.IsEmpty())
	{
		AfxMessageBox("给自己取个昵称吧!");
		return;
	}
	if(SevrIP.IsBlank())
	{
		AfxMessageBox("请填写选作P2P服务器的主机IP地址!");
		return;	
	}
	if(sevrPort.IsEmpty())
	{
		AfxMessageBox("请指定P2P服务进程的端口!");
		return;
	}

	BYTE nFild[4];
	CString sIP;
	//生成登录注册报文
	LocaIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	RegisterAddr = "RGST_ADDR;";
	RegisterAddr += nickname + "," + sIP;
	RegisterAddr += ":" + locaPort;

	//获取P2P服务进程的IP和端口
	SevrIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);	
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	//发送报文
	this->StartSndSocket(RegisterAddr,sIP,sevrPort);
	this->SetWindowTextA("已登录P2P服务器（" + sIP + ":" + sevrPort + "） - ptopTalker");

	//界面
	m_Stop.EnableWindow(false);
	m_Login.EnableWindow(false);
	m_Logout.EnableWindow(true);
	SevrIP.EnableWindow(false);
	m_SvrPrt.EnableWindow(false);
	m_nicnam.EnableWindow(false);
	m_UserList.EnableWindow(true);
	m_EditWords.EnableWindow(true);
	m_Send.EnableWindow(true);
	m_EditWords.SetFocus();
	//
//ADD
}

//ADD
LRESULT CP2PTalkerDlg::OnReadMsg(WPARAM wParam,LPARAM lParam)
{
	//接收其他端系统发来的消息
	CString str,strHead,strData;
	switch (WSAGETSELECTEVENT(lParam))
	{
	    case FD_READ:
		socklen = sizeof(m_sockSelfRcvAddr);
		recvfrom(SelfRcvSocket,(char *)&msgbuf,sizeof(msgbuf),0,(LPSOCKADDR)&m_sockSelfRcvAddr,(int *)&socklen);
		WSAAsyncSelect(SelfRcvSocket,m_hWnd,WM_CLIENT_READCLOSE,FD_READ);
		str.Format("%s",msgbuf.msg);

		//截取报文头和数据部分
		int n = str.ReverseFind(';');
		strHead = str.Left(n);
		strData = str.Right(str.GetLength() - (n + 1));

		if(strHead == "RGST_ADDR")
		{
			this->EnrolUsr(strData);
		}
		if(strHead == "UPDT_USR")
		{
			this->UpdUsr(strData);
		}
		if(strHead == "REQ_ADDR")
		{
			this->PtoPsrvProvdr(strData);
		}
		if(strHead == "RSP_ADDR")
		{
			this->SendMsgtoPer(strData);
		}
		if(strHead == "SND_MSG")
		{
			this->ShowMsgfrmPer(strData);
		}
		break;
	}
	return 0L;
}
//ADD

//ADD
void CP2PTalkerDlg::EnrolUsr(CString strMsgData)
{
	CString usrname,ipFild1,ipFild2,ipFild3,ipFild4,port;
	int n;
	//从报文中截取昵称字段
	n = strMsgData.Find(",");
	usrname = strMsgData.Left(n);
	strMsgData = strMsgData.Right(strMsgData.GetLength() - (n + 1));
	//依次截取IP和端口各个字段
	n = strMsgData.Find(".");
	ipFild1 = strMsgData.Left(n);
	strMsgData = strMsgData.Right(strMsgData.GetLength() - (n + 1));
	n = strMsgData.Find(".");
	ipFild2 = strMsgData.Left(n);
	strMsgData = strMsgData.Right(strMsgData.GetLength() - (n + 1));
	n = strMsgData.Find(".");
	ipFild3 = strMsgData.Left(n);
	strMsgData = strMsgData.Right(strMsgData.GetLength() - (n + 1));
	n = strMsgData.Find(":");
	ipFild4 = strMsgData.Left(n);
	port = strMsgData.Right(strMsgData.GetLength() - (n + 1));

	//下面开始进行用户登记处理
	BOOL BePresnc = false;              //指示这个用户是否已在服务器上注册
	for(int i = 0;i < rstUsrCont;i++)
	{
		if(CString(rstUsr[i].usrname) == usrname)
		{
			BePresnc = true;
			if(rstUsr[i].onlStat)
			{
				rstUsr[i].onlStat = false;
				onlUsrCont--;
			}
			else
			{
				//若用户上线时改变了IP，服务器上注册的用户信息也会随着同步更新
				rstUsr[i].ipFild[0] = _ttoi(ipFild1);
		        rstUsr[i].ipFild[1] = _ttoi(ipFild2);
		        rstUsr[i].ipFild[2] = _ttoi(ipFild3);
		        rstUsr[i].ipFild[3] = _ttoi(ipFild4);
		        rstUsr[i].port = atoi((LPCTSTR)port);

				rstUsr[i].onlStat = true;
				onlUsrCont++;
			}
		}
	}
	if(!BePresnc)
	{
		strcpy(rstUsr[rstUsrCont].usrname,(LPCTSTR)usrname);
		rstUsr[rstUsrCont].ipFild[0] = _ttoi(ipFild1);
		rstUsr[rstUsrCont].ipFild[1] = _ttoi(ipFild2);
		rstUsr[rstUsrCont].ipFild[2] = _ttoi(ipFild3);
		rstUsr[rstUsrCont].ipFild[3] = _ttoi(ipFild4);
		rstUsr[rstUsrCont].port = atoi((LPCTSTR)port); 
		rstUsr[rstUsrCont].onlStat = true;
		rstUsrCont++;
		onlUsrCont++;
	}

	//更新用户……以下为测试代码
	m_UserList.EnableWindow(true);
	m_UserList.ResetContent();
	m_MessageList.SetWindowTextA("");
	OnlUsrInfo = "UPDT_USR;";
	for(int i = 0;i < rstUsrCont;i++)
	{
		if(rstUsr[i].onlStat)
		{
			OnlUsrInfo += CString(rstUsr[i].usrname) + "&";                    //生成更新用户类报文
			m_UserList.AddString(CString(rstUsr[i].usrname));

			CString sIP,sP,onlUsrStateView;
			sIP.Format("%d.%d.%d.%d",rstUsr[i].ipFild[0],rstUsr[i].ipFild[1],rstUsr[i].ipFild[2],rstUsr[i].ipFild[3]);
			sP.Format("%d",rstUsr[i].port);
			onlUsrStateView = CString(rstUsr[i].usrname) + " -IP:";
			onlUsrStateView += sIP + " 端口:";
			onlUsrStateView += sP + "\r\n";
			m_MessageList.ReplaceSel(onlUsrStateView);

		}
	}
	for(int i = 0;i < rstUsrCont;i++)
	{
		if(rstUsr[i].onlStat)
		{
			CString sIP,sP;
			sIP.Format("%d.%d.%d.%d",rstUsr[i].ipFild[0],rstUsr[i].ipFild[1],rstUsr[i].ipFild[2],rstUsr[i].ipFild[3]);
			sP.Format("%d",rstUsr[i].port);
	        this->StartSndSocket(OnlUsrInfo,sIP,sP);
		}
	}
	//测试代码
}
//ADD

//ADD
void CP2PTalkerDlg::UpdUsr(CString strMsgData)
{
	CString array[100];
	int b = 0;
	for( int i = 0; i < strMsgData.GetLength(); i++ )
	{
		if(i != (strMsgData.GetLength() - 1))
		{
			if ( strMsgData[i] == '&' )
			{
				b ++;
			}
			else
			{
				array[b] = array[b] + strMsgData[i];
			}
		}
	}
	m_UserList.ResetContent();
	for(int j = 0; j < b + 1; j ++)
	{
		m_UserList.AddString(array[j]);
	}
}
//ADD

//ADD
void CP2PTalkerDlg::PtoPsrvProvdr(CString strMsgData)
{
	CString usrname,ip,port,perUsrAddr;
	int n;
	//从报文中截取昵称字段
	n = strMsgData.Find(",");
	usrname = strMsgData.Left(n);
	strMsgData = strMsgData.Right(strMsgData.GetLength() - (n + 1));

	//在本地服务器上搜索用户请求的IP地址
	for(int i = 0;i < rstUsrCont;i++)
	{
		if(CString(rstUsr[i].usrname) == usrname)
		{
			//找到匹配的用户之后，组装成P2P服务响应报文
			CString perIP,perPort;
			perIP.Format("%d.%d.%d.%d",rstUsr[i].ipFild[0],rstUsr[i].ipFild[1],rstUsr[i].ipFild[2],rstUsr[i].ipFild[3]);
			perPort.Format("%d",rstUsr[i].port);
			perUsrAddr = usrname + ",";
			perUsrAddr += perIP + ":";
			perUsrAddr += perPort;
			PtoPsrvRspse = "RSP_ADDR;" + perUsrAddr;
			break;
		}
	}
	//截取请求发送者的IP和端口
	n = strMsgData.Find(":");
	ip = strMsgData.Left(n);
	port = strMsgData.Right(strMsgData.GetLength() - (n + 1));

	//向用户返回响应报文
	this->StartSndSocket(PtoPsrvRspse,ip,port);
}
//ADD

//ADD
void CP2PTalkerDlg::SendMsgtoPer(CString strMsgData)
{
	CString ip,port;
	int n;
	//从报文中解析出对方地址信息
	n = strMsgData.Find(",");
	strMsgData = strMsgData.Right(strMsgData.GetLength() - (n + 1));
	//截取对方的IP和端口
	n = strMsgData.Find(":");
	ip = strMsgData.Left(n);
	port = strMsgData.Right(strMsgData.GetLength() - (n + 1));

	//组装出携带聊天信息的消息
	UpdateData();
	if(strMessage == "")
	{
		AfxMessageBox("不能发送空消息!");
		m_EditWords.SetFocus();
		return;
	}
	CTime time = CTime::GetCurrentTime();
	CString t = time.Format("%H:%M:%S");
	MsgTalktoPeer = "SND_MSG;" + nickname + ",";	
	MsgTalktoPeer += t + "\r\n   " + strMessage + "\r\n";

	//向对方发送聊天信息
	this->StartSndSocket(MsgTalktoPeer,ip,port);
	MsgTalktoPeer = "\r\n" + nickname + "   " + t + "\r\n   " + strMessage + "\r\n";
	m_MessageList.ReplaceSel(MsgTalktoPeer);
	strMessage = "";
	UpdateData(FALSE);
	m_EditWords.SetFocus();
}
//ADD

//ADD
void CP2PTalkerDlg::ShowMsgfrmPer(CString strMsgData)
{
	CString usrname,MsgfrmPer,str;
	int n;
	//从报文中取出昵称和聊天信息字段
	n = strMsgData.Find(",");
	usrname = strMsgData.Left(n);
	MsgfrmPer = strMsgData.Right(strMsgData.GetLength() - (n + 1));

	//聊天内容显示
	str = "\r\n" + usrname + "   " + MsgfrmPer;
	m_MessageList.ReplaceSel(str);
}
//ADD

void CP2PTalkerDlg::OnLogout()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	UpdateData();
	BYTE nFild[4];
	CString sIP;

	//生成登录注册报文
	LocaIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	RegisterAddr = "RGST_ADDR;";
	RegisterAddr += nickname + "," + sIP;
	RegisterAddr += ":" + locaPort;

	//获取P2P服务进程的IP和端口
	SevrIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);	
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	//发送报文
	this->StartSndSocket(RegisterAddr,sIP,sevrPort);
	m_UserList.ResetContent();
	this->SetWindowTextA("注销成功! - ptopTalker");

	//界面
	m_Stop.EnableWindow(true);
	m_Login.EnableWindow(true);
	m_Logout.EnableWindow(false);
	SevrIP.EnableWindow(true);
	m_SvrPrt.EnableWindow(true);
	m_nicnam.EnableWindow(true);
	m_UserList.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
	m_nicnam.SetFocus();
	//
//ADD
}

//ADD
void CP2PTalkerDlg::StartSndSocket(CString msgtoSnd,CString sIP,CString sPort)
{
	//另启一个专门用于发消息的Socket进程
	SelfSndSocket = socket(PF_INET,SOCK_DGRAM,0);
    if(SelfSndSocket == INVALID_SOCKET)
	{
		m_MessageList.ReplaceSel("创建socket失败!\r\n");
        return;
	}
    m_sockSelfSndAddr.sin_family = AF_INET;
    m_sockSelfSndAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 
    m_sockSelfSndAddr.sin_port = htons(8888);
    if(bind(SelfSndSocket,(LPSOCKADDR)&m_sockSelfSndAddr,sizeof(m_sockSelfSndAddr)) == SOCKET_ERROR)
    {
		m_MessageList.ReplaceSel("绑定失败!\r\n");
        return;
	}

	//设置发送参数
	m_sockAddrto.sin_family = AF_INET;
    m_sockAddrto.sin_addr.S_un.S_addr = inet_addr(sIP); 
    m_sockAddrto.sin_port = htons(atoi(sPort));
	strcpy(msgbuf.msg,(LPCTSTR)msgtoSnd);
	msgbuf.i = 0;

	//发送
	if(sendto(SelfSndSocket,(char *)&msgbuf,sizeof(msgbuf),0,(LPSOCKADDR)&m_sockAddrto,sizeof(m_sockAddrto)) == SOCKET_ERROR)
	{
		m_MessageList.ReplaceSel("发送数据失败!\r\n");
	}
	closesocket(SelfSndSocket);   //发消息的套接字在用完后要及时关闭，以便其他端系统进程也能随时共享使用它
}

void CP2PTalkerDlg::OnSend()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	//选择对方用户名
	int nSel;
	nSel = m_UserList.GetCurSel();
	if(nSel == LB_ERR)
	{
		AfxMessageBox("请先从在线用户列表中选择对方网名!");
		return;
	}
	CString UsrSel;
	m_UserList.GetText(nSel,UsrSel);
	UpdateData();
	if(UsrSel == nickname)
	{
		AfxMessageBox("不能向自身发消息!");
		return;
	}
	//生成请求P2P服务类的报文
	BYTE nFild[4];
	CString sIP;
	LocaIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	PtoPsrvReqst = "REQ_ADDR;";
	PtoPsrvReqst += UsrSel + "," + sIP;
	PtoPsrvReqst += ":" + locaPort;

	//获取P2P服务进程的IP和端口
	SevrIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);	
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	//发送报文
	this->StartSndSocket(PtoPsrvReqst,sIP,sevrPort);
//ADD
}

void CP2PTalkerDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
//ADD
}
