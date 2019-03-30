// ChatClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"

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


// CChatClientDlg �Ի���




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


// CChatClientDlg ��Ϣ�������

BOOL CChatClientDlg::OnInitDialog()
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
	m_ClientSocket=NULL;
	m_archiveIn=NULL;
	m_archiveOut=NULL;
	m_socketfile=NULL;

	//���湦������
	m_ButtonDisconnect.EnableWindow(false);
	m_ButtonClear.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	//���湦������
//ADD

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatClientDlg::OnPaint()
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
	m_ListWords.AddString("�������˶Ͽ���");
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
	SocketReset();

	//���湦������
	ServerIP.EnableWindow();
	ServerPort.EnableWindow();
	m_ButtonConnect.EnableWindow();
	m_ButtonDisconnect.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	m_ButtonExit.EnableWindow();
    //���湦������
}
void CChatClientDlg::OnReceive()
{
	*m_archiveIn>>m_Input;
	m_archiveIn->Flush();
	m_ListWords.AddString("�յ���"+m_Input);
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
}
//ADD


void CChatClientDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	if(!AfxSocketInit())
	{
		MessageBox("WindowSocket initial failed!","Receive",MB_ICONSTOP);
		return;
	}
	m_ClientSocket=new MySocket;
	m_ClientSocket->GetDlg(this);
	m_ClientSocket->Create();   // �����ͻ���Socket

	BYTE nFild[4];
	CString sIP;
	UpdateData();
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	if(!m_ClientSocket->Connect(sIP,sPort)) //������������
	{
		AfxMessageBox("����ʧ�ܣ��������ԣ�");
		return;
	}
	else
	{
		m_ListWords.AddString("���ӷ������ɹ���");
	    m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);

	    m_socketfile=new CSocketFile(m_ClientSocket);
	    m_archiveIn=new CArchive(m_socketfile,CArchive::load);
	    m_archiveOut=new CArchive(m_socketfile,CArchive::store);
	}

	//���湦������
	ServerIP.EnableWindow(false);
	ServerPort.EnableWindow(false);
	m_ButtonConnect.EnableWindow(false);
	m_ButtonDisconnect.EnableWindow();
	m_EditWords.EnableWindow();
	m_ButtonSend.EnableWindow();
	m_ButtonExit.EnableWindow(false);
	m_ButtonClear.EnableWindow();
	//���湦������
//ADD
}

void CChatClientDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	SocketReset();
	m_ListWords.AddString("�ӷ������Ͽ�");

	//���湦������
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
	ServerIP.EnableWindow();
	ServerPort.EnableWindow();
	m_ButtonConnect.EnableWindow();
	m_ButtonDisconnect.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	m_ButtonExit.EnableWindow();
	//���湦������
//ADD
}

void CChatClientDlg::OnBnClickedButton3()
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

void CChatClientDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	m_ListWords.ResetContent();
//ADD
}

void CChatClientDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();//��ʾ�����ڡ��Ի���
//ADD

}
