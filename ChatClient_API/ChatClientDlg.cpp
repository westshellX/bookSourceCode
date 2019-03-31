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
	, sPort(_T(""))
	, m_sWords(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
	DDX_Control(pDX, IDC_EDIT2, ServerPort);
	DDX_Text(pDX, IDC_EDIT2, sPort);
	DDX_Control(pDX, IDC_LIST1, m_ListWords);
	DDX_Control(pDX, IDC_EDIT1, m_EditWords);
	DDX_Text(pDX, IDC_EDIT1, m_sWords);
	DDX_Control(pDX, IDC_BUTTON3, m_ButtonConnect);
	DDX_Control(pDX, IDC_BUTTON4, m_ButtonDisconnect);
	DDX_Control(pDX, IDC_BUTTON5, m_ButtonClear);
	DDX_Control(pDX, IDC_BUTTON2, m_ButtonSend);
	DDX_Control(pDX, IDCANCEL, m_ButtonExit);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &CChatClientDlg::OnConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatClientDlg::OnSend)
	ON_BN_CLICKED(IDC_BUTTON4, &CChatClientDlg::OnDisconnect)
	ON_BN_CLICKED(IDC_BUTTON5, &CChatClientDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CChatClientDlg::OnBnClickedButton1)
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
	//�����ʼ��
	m_ButtonDisconnect.EnableWindow(false);
	m_ButtonClear.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	//�����ʼ��
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


void CChatClientDlg::OnConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	WSADATA wsd;
	WSAStartup(MAKEWORD(2,2),&wsd);
	m_client = socket(AF_INET,SOCK_STREAM,0);
	//�������˵�ַ
	sockaddr_in serveraddr;

	UpdateData();
	if(ServerIP.IsBlank())
	{
		AfxMessageBox("��ָ��������IP!");
		return;	
	}
	if(sPort.IsEmpty())
	{
		AfxMessageBox("��ָ���˿�!");
		return;
	}
	//��ȡ���������̵�IP�Ͷ˿�
	BYTE nFild[4];
	CString sIP;
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.S_un.S_addr = inet_addr(sIP); 
    serveraddr.sin_port = htons(atoi(sPort));

	if(connect(m_client,(sockaddr*)&serveraddr,sizeof(serveraddr)) != 0)
	{
		MessageBox("����ʧ��");
		return;
	}
	else
	{
		m_ListWords.AddString("���ӷ������ɹ�!");
	    m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
	}
	WSAAsyncSelect(m_client,m_hWnd,10000,FD_READ|FD_CLOSE);

	//��������
	ServerIP.EnableWindow(false);
	ServerPort.EnableWindow(false);
	m_ButtonConnect.EnableWindow(false);
	m_ButtonDisconnect.EnableWindow();
	m_EditWords.EnableWindow();
	m_ButtonSend.EnableWindow();
	m_ButtonExit.EnableWindow(false);
	m_ButtonClear.EnableWindow();
	//��������
//ADD
}

//ADD
void CChatClientDlg::ReceiveData()
{
	char buffer[1024];
	//���շ������˴���������
	int num = recv(m_client,buffer,1024,0);
	buffer[num] = '\0';
	//�����յ�������ӵ��б����
	CString sTemp;
	sTemp.Format("�յ���%s",buffer);
	WSAAsyncSelect(m_client,m_hWnd,10000,FD_READ|FD_CLOSE);
	m_ListWords.AddString(sTemp);
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
}

void CChatClientDlg::CloseSock()
{
	m_ListWords.AddString("�������˶Ͽ���");
	m_ListWords.SetTopIndex(m_ListWords.GetCount() - 1);
	closesocket(m_client);

	//��������
	ServerIP.EnableWindow();
	ServerPort.EnableWindow();
	m_ButtonConnect.EnableWindow();
	m_ButtonDisconnect.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	m_ButtonExit.EnableWindow();
	//��������
}
//ADD

BOOL CChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	if(pMsg->message == 10000)
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

void CChatClientDlg::OnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	//�����������Ϣ
	UpdateData();
	if(m_sWords.IsEmpty())
	{
	    AfxMessageBox("���͵���Ϣ����Ϊ��!");
		return;
	}
	//��ʼ��������
	int i = send(m_client,m_sWords.GetBuffer(0),m_sWords.GetLength(),0);
	m_ListWords.AddString("���ͣ�" + m_sWords);
	m_ListWords.SetTopIndex(m_ListWords.GetCount()-1);
//ADD
}

void CChatClientDlg::OnDisconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	//�Ͽ��������������
	closesocket(m_client);
	m_ListWords.AddString("�ӷ������Ͽ�");
	//��������
	m_ListWords.SetTopIndex(m_ListWords.GetCount() - 1);
	ServerIP.EnableWindow();
	ServerPort.EnableWindow();
	m_ButtonConnect.EnableWindow();
	m_ButtonDisconnect.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_ButtonSend.EnableWindow(false);
	m_ButtonExit.EnableWindow();
	//��������
//ADD
}

void CChatClientDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	m_ListWords.ResetContent();
//ADD
}

void CChatClientDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();//��ʾ�����ڡ��Ի���
//ADD
}
