// ChatServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CChatServerDlg �Ի���




CChatServerDlg::CChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatServerDlg::IDD, pParent)
	, sPort(0)
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
	DDX_Control(pDX, IDC_EDIT2, m_EditWords);
	DDX_Text(pDX, IDC_EDIT2, m_sWords);
	DDX_Control(pDX, IDC_LIST1, m_ListWords);
	DDX_Control(pDX, IDC_BUTTON3, m_ButtonDisconnect);
	DDX_Control(pDX, IDC_BUTTON5, m_ButtonClear);
	DDX_Control(pDX, IDCANCEL, m_ButtonExit);
	DDX_Control(pDX, IDC_BUTTON1, m_ButtonListen);
	DDX_Control(pDX, IDC_BUTTON2, m_ButtonStopListen);
	DDX_Control(pDX, IDC_BUTTON4, m_ButtonSend);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CChatServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CChatServerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatServerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CChatServerDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CChatServerDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CChatServerDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CChatServerDlg ��Ϣ�������

BOOL CChatServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
//ADD
	m_ServerSocket=NULL;
	m_ListenSocket=NULL;
	m_archiveIn=NULL;
	m_archiveOut=NULL;
	m_socketfile=NULL;

	//���湦������
	m_ButtonStopListen.EnableWindow(false);
	m_ButtonDisconnect.EnableWindow(false);
	m_ButtonClear.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
    //���湦������
//ADD

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//ADD
void CChatServerDlg::SocketReset()
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
	if(m_ServerSocket!=NULL)
	{
		delete m_ServerSocket;
		m_ServerSocket=NULL;
	}
}
void CChatServerDlg::OnClose()
{
	m_ListWords.AddString("�ͻ��˶Ͽ�����");
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
	SocketReset();

	//���湦������
	m_ButtonDisconnect.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
    //���湦������
}
void CChatServerDlg::OnReceive()
{
	*m_archiveIn>>m_Input;
	m_archiveIn->Flush();
	m_ListWords.AddString("�յ���"+m_Input);
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
}
void CChatServerDlg::OnAccept()
{
	m_ServerSocket=new MySocket;
	m_ServerSocket->GetDlg(this);
	m_ListenSocket->Accept(*m_ServerSocket);
	m_ServerSocket->AsyncSelect(FD_READ|FD_CLOSE);

	m_socketfile=new CSocketFile(m_ServerSocket);
	m_archiveIn=new CArchive(m_socketfile,CArchive::load);
	m_archiveOut=new CArchive(m_socketfile,CArchive::store);

	m_ListWords.AddString("������һ���ͻ��˵���������");
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);

	//���湦������
	m_ButtonDisconnect.EnableWindow();
	m_EditWords.EnableWindow();
	m_ButtonSend.EnableWindow();
    //���湦������
}
//ADD
void CChatServerDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	if(!AfxSocketInit())       //��ʼ���׽���
	{
		MessageBox("WindowSocket initial failed!","Send",MB_ICONSTOP);
		return;
	}
	m_ListenSocket=new MySocket;
	m_ListenSocket->GetDlg(this);

	BYTE nFild[4];
	CString sIP,sP;
	UpdateData();
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	sP.Format("%d",sPort);
	m_ListenSocket->Create(sPort,1,sIP); //��������˼���Socket
	m_ListenSocket->Listen(1);        //��ʼ����
	m_ListWords.AddString("������ʼ��");
	m_ListWords.AddString("��ַ "+sIP+"  �˿� "+sP);
	m_ListWords.AddString("�ȴ��ͻ������ӡ���");

	//���湦������
    m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
	ServerIP.EnableWindow(false);
	ServerPort.EnableWindow(false);
	m_ButtonListen.EnableWindow(false);
	m_ButtonStopListen.EnableWindow();
	m_ButtonClear.EnableWindow();
	m_ButtonExit.EnableWindow(false);
	//���湦������
//ADD
}

void CChatServerDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	SocketReset();
	m_ListWords.AddString("��ͻ��˶Ͽ�");

	//���湦������
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
	m_ButtonDisconnect.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
    //���湦������
//ADD
}

void CChatServerDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	if(m_ListenSocket!=NULL)
	{
		delete m_ListenSocket;
		m_ListenSocket=NULL;
	}
	m_ListWords.AddString("ֹͣ����");

	//���湦������
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
	ServerIP.EnableWindow();
	ServerPort.EnableWindow();
	m_ButtonListen.EnableWindow();
	m_ButtonStopListen.EnableWindow(false);
	m_ButtonExit.EnableWindow();
    //���湦������
//ADD
}

void CChatServerDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	UpdateData();
	*m_archiveOut<<m_sWords;
	m_archiveOut->Flush();
	m_ListWords.AddString("���ͣ�"+m_sWords);
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
//ADD
}

void CChatServerDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	m_ListWords.ResetContent();
//ADD
}

void CChatServerDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������\
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();//��ʾ�����ڡ��Ի���
//ADD
}
