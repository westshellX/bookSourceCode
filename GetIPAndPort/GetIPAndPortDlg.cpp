// GetIPAndPortDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GetIPAndPort.h"
#include "GetIPAndPortDlg.h"

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


// CGetIPAndPortDlg 对话框




CGetIPAndPortDlg::CGetIPAndPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetIPAndPortDlg::IDD, pParent)
	, strport(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetIPAndPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Control(pDX, IDC_EDIT1, m_port);
	DDX_Control(pDX, IDC_EDIT2, m_showIpAndPort);
	DDX_Text(pDX, IDC_EDIT1, strport);
}

BEGIN_MESSAGE_MAP(CGetIPAndPortDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CGetIPAndPortDlg::OnShowIpAndPort)
	ON_BN_CLICKED(IDC_BUTTON2, &CGetIPAndPortDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CGetIPAndPortDlg 消息处理程序

BOOL CGetIPAndPortDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGetIPAndPortDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetIPAndPortDlg::OnPaint()
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
HCURSOR CGetIPAndPortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGetIPAndPortDlg::OnShowIpAndPort()
{
	// TODO: 在此添加控件通知处理程序代码

	BYTE nFild[4];			//分别存放IP的四个字段
	CString sip;            //IP地址的字符串形式（可以直接显示在界面上的）
	UpdateData();           //刷新对话框界面，获取用户输入

	//验证输入是否合法
	if(m_ip.IsBlank())      //若用户没有填写IP，提示他填写
	{
		AfxMessageBox("请填写IP地址!");
		return;
	}

	if(strport.IsEmpty())	//若用户忘了制定端口号，提醒其指定
	{
		AfxMessageBox("请指定进程端口!");
		return;
	}

	//获取用户输入的IP地址值
	m_ip.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);

	//将IP地址格式化为可以在电脑屏幕上显示的字符串
	sip.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	//在界面上显示用户输入的网络进程地址（包括所在主机的IP和端口）
	m_showIpAndPort.SetWindowTextA(sip + " :" + strport);
	m_ip.SetFocus();		//焦点回到IP地址栏
}

void CGetIPAndPortDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();			//显示“关于”对话框
}
