// SelfChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SelfChat.h"
#include "SelfChatDlg.h"
//ADD
//#include "ClientSocket.h"
#include "tagHeader.h"
//ADD

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


// CSelfChatDlg �Ի���




CSelfChatDlg::CSelfChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelfChatDlg::IDD, pParent)
	, m_strName(_T(""))
	, m_strMessage(_T(""))
	, strport(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSelfChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
	DDX_Control(pDX, IDC_LIST1, m_UserList);
	DDX_Control(pDX, IDC_EDIT3, m_MessageList);
	DDX_Text(pDX, IDC_EDIT4, m_strMessage);
	DDX_Control(pDX, IDC_EDIT2, m_port);
	DDX_Text(pDX, IDC_EDIT2, strport);
	DDX_Control(pDX, IDC_EDIT4, m_EditWords);
	DDX_Control(pDX, IDC_EDIT1, m_Usr);
	DDX_Control(pDX, IDC_BUTTON1, m_Enter);
	DDX_Control(pDX, IDC_BUTTON2, m_Quit);
	DDX_Control(pDX, IDC_BUTTON3, m_Send);
	DDX_Control(pDX, IDC_BUTTON4, m_Refresh);
	DDX_Control(pDX, IDCANCEL, m_Exit);
}

BEGIN_MESSAGE_MAP(CSelfChatDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CSelfChatDlg::OnEnter)
	ON_BN_CLICKED(IDC_BUTTON2, &CSelfChatDlg::OnQuit)
	ON_BN_CLICKED(IDC_BUTTON3, &CSelfChatDlg::OnSend)
	ON_BN_CLICKED(IDC_BUTTON4, &CSelfChatDlg::OnRefresh)
	ON_BN_CLICKED(IDC_BUTTON5, &CSelfChatDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CSelfChatDlg ��Ϣ�������

BOOL CSelfChatDlg::OnInitDialog()
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
	m_pSocket=NULL;

	//��ʼ����
	m_Usr.SetFocus();
	m_Quit.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
	m_Refresh.EnableWindow(false);
//ADD

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSelfChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSelfChatDlg::OnPaint()
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
HCURSOR CSelfChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSelfChatDlg::OnEnter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	UpdateData();
	m_pSocket = new CClientSocket;
	m_pSocket->GetDlg(this);

	BYTE nFild[4];
	CString sip;
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);	
	sip.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	if(m_strName.IsEmpty())
	{
		AfxMessageBox("���Լ�ȡ���ǳư�!");
		return;
	}
	if(sip.IsEmpty())
	{
		AfxMessageBox("��ָ��IP��ַ!");
		return;	
	}
	if(strport.IsEmpty())
	{
		AfxMessageBox("��ָ�����Ӷ˿�!");
		return;
	}

	if(!m_pSocket->Create())
	{
		AfxMessageBox("���紴�����󣡣���");
		m_pSocket->Close();
		return;
	}
	if(!m_pSocket->Connect(sip,atoi(strport)))
	{
		AfxMessageBox("���ӷ�����ʧ�ܣ�����");
		m_pSocket->Close();
		return;	
	}

	//����
	m_Usr.EnableWindow(false);
	ServerIP.EnableWindow(false);
	m_port.EnableWindow(false);
	m_Enter.EnableWindow(false);
	m_Quit.EnableWindow(true);
	m_EditWords.EnableWindow(true);
	m_EditWords.SetFocus();
	m_Send.EnableWindow(true);
	m_Refresh.EnableWindow(true);
	m_Exit.EnableWindow(false);
	//����

	Header head;
	head.type = LOGIN_IO;
	head.len = m_strName.GetLength();

	m_pSocket->Send((char *)&head,sizeof(Header));
	m_pSocket->Send(m_strName,m_strName.GetLength());

	theApp.m_strName = m_strName;
	m_MessageList.SetWindowTextA("");
	this->SetWindowTextA(m_strName + "-SelfChat");

//ADD
}

void CSelfChatDlg::OnQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	if(m_pSocket)
	{
		m_pSocket->Close();
		delete m_pSocket;
	}
	m_UserList.ResetContent();
	m_MessageList.ReplaceSel("���Ѿ��˳���, лл���!");
	this->SetWindowTextA("�����ҿͻ���-SelfChat");

	//����
	m_Usr.EnableWindow(true);
	m_Usr.SetFocus();
	ServerIP.EnableWindow(true);
	m_port.EnableWindow(true);
	m_Enter.EnableWindow(true);
	m_Quit.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
	m_Exit.EnableWindow(true);
//ADD
}

void CSelfChatDlg::OnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	UpdateData();
	if(m_strMessage == "")
	{
		AfxMessageBox("���ܷ��Ϳ���Ϣ!");
		m_EditWords.SetFocus();
		return;
	}
	Header head;
	head.type = SEND_MESSAGE;
	head.len = m_strMessage.GetLength();
	
	m_pSocket->Send((char *)&head,sizeof(Header));

	if(m_pSocket->Send(m_strMessage,m_strMessage.GetLength()))
	{
		m_strMessage = "";
		UpdateData(FALSE);
		m_EditWords.SetFocus();
		return;
	}
	else
	{
		AfxMessageBox("���紫�����");		
	}
//ADD
}

//ADD
BOOL CSelfChatDlg::GetMsgFromRoom()
{
	char buff[1000];
	memset(buff,0,sizeof(buff));
	m_pSocket->Receive(buff, sizeof(buff));
	m_pSocket->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
	
	CString strTemp = buff;
	strTemp += "\r\n";
	m_MessageList.ReplaceSel(strTemp);
	return TRUE;
}
//ADD

//ADD
void  CSelfChatDlg::UpdateUser()
{
    char buff[1000];
	memset(buff,0,sizeof(buff));
	m_pSocket->Receive(buff, sizeof(buff));
	m_pSocket->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
	
	CString user_info = buff;

	CString array[100];
	int b = 0;
	for( int i = 0; i < user_info.GetLength(); i++ )
	{
		if(i != (user_info.GetLength() - 1))
		{
			if ( user_info[i] == '&' )
			{
				b ++;
			}
			else
			{
				array[b] = array[b] + user_info[i];
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
void CSelfChatDlg::OnRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	m_MessageList.SetWindowTextA("");
//ADD
}

void CSelfChatDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
//ADD
}
