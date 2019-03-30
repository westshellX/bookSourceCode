// ChatClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"

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


// CChatClientDlg 对话框




CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatClientDlg::IDD, pParent)
	, sPort(0)
	, m_sWords(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
	DDX_Control(pDX, IDC_EDIT1, ServerPort);
	DDX_Text(pDX, IDC_EDIT1, sPort);
	DDX_Control(pDX, IDC_EDIT2, m_EditWords);
	DDX_Text(pDX, IDC_EDIT2, m_sWords);
	DDX_Control(pDX, IDC_LIST1, m_ListWords);
	DDX_Control(pDX, IDC_BUTTON1, m_ButtonConnect);
	DDX_Control(pDX, IDC_BUTTON2, m_ButtonDisconnect);
	DDX_Control(pDX, IDC_BUTTON4, m_ButtonClear);
	DDX_Control(pDX, IDC_BUTTON3, m_ButtonSend);
	DDX_Control(pDX, IDCANCEL, m_ButtonExit);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CChatClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CChatClientDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CChatClientDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CChatClientDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CChatClientDlg 消息处理程序

BOOL CChatClientDlg::OnInitDialog()
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
	m_ClientSocket=NULL;
	m_archiveIn=NULL;
	m_archiveOut=NULL;
	m_socketfile=NULL;

	//界面功能完善
	m_ButtonDisconnect.EnableWindow(false);
	m_ButtonClear.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	//界面功能完善
//ADD

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatClientDlg::OnPaint()
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
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//ADD
void CChatClientDlg::SocketReset()
{
	if(m_archiveIn!=NULL)
	{
		delete m_archiveIn;
		m_archiveIn=NULL;
	}
	if(m_archiveOut!=NULL)
	{
		delete m_archiveOut;
		m_archiveOut=NULL;
	}
	if(m_socketfile!=NULL)
	{
		delete m_socketfile;
		m_socketfile=NULL;
	}
	if(m_ClientSocket!=NULL)
	{
		delete m_ClientSocket;
		m_ClientSocket=NULL;
	}
}
void CChatClientDlg::OnClose()
{
	m_ListWords.AddString("服务器端断开了");
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
	SocketReset();

	//界面功能完善
	ServerIP.EnableWindow();
	ServerPort.EnableWindow();
	m_ButtonConnect.EnableWindow();
	m_ButtonDisconnect.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	m_ButtonExit.EnableWindow();
    //界面功能完善
}
void CChatClientDlg::OnReceive()
{
	*m_archiveIn>>m_Input;
	m_archiveIn->Flush();
	m_ListWords.AddString("收到："+m_Input);
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
}
//ADD


void CChatClientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	if(!AfxSocketInit())
	{
		MessageBox("WindowSocket initial failed!","Receive",MB_ICONSTOP);
		return;
	}
	m_ClientSocket=new MySocket;
	m_ClientSocket->GetDlg(this);
	m_ClientSocket->Create();   // 创建客户端Socket

	BYTE nFild[4];
	CString sIP;
	UpdateData();
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	if(!m_ClientSocket->Connect(sIP,sPort)) //发起连接请求
	{
		AfxMessageBox("连接失败，请您重试！");
		return;
	}
	else
	{
		m_ListWords.AddString("连接服务器成功！");
	    m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);

	    m_socketfile=new CSocketFile(m_ClientSocket);
	    m_archiveIn=new CArchive(m_socketfile,CArchive::load);
	    m_archiveOut=new CArchive(m_socketfile,CArchive::store);
	}

	//界面功能完善
	ServerIP.EnableWindow(false);
	ServerPort.EnableWindow(false);
	m_ButtonConnect.EnableWindow(false);
	m_ButtonDisconnect.EnableWindow();
	m_EditWords.EnableWindow();
	m_ButtonSend.EnableWindow();
	m_ButtonExit.EnableWindow(false);
	m_ButtonClear.EnableWindow();
	//界面功能完善
//ADD
}

void CChatClientDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	SocketReset();
	m_ListWords.AddString("从服务器断开");

	//界面功能完善
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
	ServerIP.EnableWindow();
	ServerPort.EnableWindow();
	m_ButtonConnect.EnableWindow();
	m_ButtonDisconnect.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	m_ButtonExit.EnableWindow();
	//界面功能完善
//ADD
}

void CChatClientDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	UpdateData();
	*m_archiveOut<<m_sWords;
	m_archiveOut->Flush();
	m_ListWords.AddString("发送："+m_sWords);
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
//ADD
}

void CChatClientDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	m_ListWords.ResetContent();
//ADD
}

void CChatClientDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();//显示“关于”对话框
//ADD

}
