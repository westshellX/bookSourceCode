// UDProcsCommDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDProcsComm.h"
#include "UDProcsCommDlg.h"

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


// CUDProcsCommDlg �Ի���




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


// CUDProcsCommDlg ��Ϣ�������

BOOL CUDProcsCommDlg::OnInitDialog()
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

	//ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
//ADD
	IPLocal.SetFocus();
	list.EnableWindow(false);
	m_Stop.EnableWindow(false);
	IPDest.EnableWindow(false);
	PortDest.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
//ADD

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUDProcsCommDlg::OnPaint()
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
HCURSOR CUDProcsCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUDProcsCommDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	UpdateData();
	if(IPLocal.IsBlank())
	{
		AfxMessageBox("������IP��ַ!");
		return;	
	}
	if(LocalPort.IsEmpty())
	{
		AfxMessageBox("�����ö˿ں�!");
		return;
	}
	//��ʼ�����
    WSADATA wsaData;
    int iErrorCode;
    if (WSAStartup(MAKEWORD(2,1),&wsaData)) //����Windows Sockets DLL
	{ 
         list.AddString("Winsock�޷���ʼ��!");
         WSACleanup();
         return;
	}

	list.AddString("��ʼ����Socket��");

	ServerSocket = socket(PF_INET,SOCK_DGRAM,0);    //�����������̵�Socket������ΪSOCK_DGRAM�������ӵ�ͨ��

    if(ServerSocket == INVALID_SOCKET)
	{
         list.AddString("����socketʧ��!");
         return;
	}

	//��ȡ�������̵�IP�Ͷ˿�
	BYTE nFild[4];
	CString sIP;
	IPLocal.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

    m_sockServerAddr.sin_family = AF_INET;
    m_sockServerAddr.sin_addr.s_addr = inet_addr(sIP); 
    m_sockServerAddr.sin_port = htons(atoi(LocalPort));

	socklen = sizeof(m_sockServerAddr);

    if (bind(ServerSocket,(LPSOCKADDR)&m_sockServerAddr,sizeof(m_sockServerAddr)) == SOCKET_ERROR) //�����õĶ˿ڰ�
    {
	    list.AddString("��ʧ��!");
        return;
	}
	iErrorCode = WSAAsyncSelect(ServerSocket,m_hWnd,WM_CLIENT_READCLOSE,FD_READ);

    // ������Ӧ���ݸ����ڵ���ϢΪWM_SERVER_ACCEPT �������Զ�����Ϣ

    if (iErrorCode == SOCKET_ERROR) 
	{
         list.AddString("WSAAsyncSelect�趨ʧ��!�������������������Ϣ");
         return;
	}


 	list.AddString("�������������ɹ�!");
	list.AddString("��ַ " + sIP + "  �˿� " + LocalPort);
	this->SetWindowTextA("����Ӧ�ý��̣�" + sIP + ":" + LocalPort + "��-UDProcsComm");

	//����
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
	//����
    return; 
//ADD

	CDialog::OnOK();
}

void CUDProcsCommDlg::OnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	//������ֹͣ����ʱ����SOCKET���
	list.AddString("���ڹر�Socket��");
	closesocket(ServerSocket);
	WSACleanup();
	list.AddString("��������ֹͣ����!");

	//����
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
	//����

//ADD
}

void CUDProcsCommDlg::OnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	//��������
	UpdateData();
	if(IPDest.IsBlank())
	{
		AfxMessageBox("��ָ��Ŀ���������������IP��ַ!");
		return;	
	}
	if(DestPort.IsEmpty())
	{
		AfxMessageBox("��ָ��Ŀ����̵Ķ˿ں�!");
		return;
	}
	//��ȡĿ����̵�IP�Ͷ˿�
	BYTE nFild[4];
	CString sIP;
	IPDest.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	m_sockAddrto.sin_family = AF_INET;
    m_sockAddrto.sin_addr.s_addr = inet_addr(sIP); 
    m_sockAddrto.sin_port = htons(atoi(DestPort));
	if(str.IsEmpty())
	{
	    AfxMessageBox("���͵���Ϣ����Ϊ��!");
		return;
	}
	strcpy(msg.msg,(LPCTSTR)str);
	msg.i = 0;
	if(sendto(ServerSocket,(char *)&msg,sizeof(msg),0,(LPSOCKADDR)&m_sockAddrto,sizeof(m_sockAddrto)) == SOCKET_ERROR)
	{
		list.AddString("��������ʧ��!");
	};
	str.Empty();
	UpdateData(FALSE);
//ADD
}

//ADD
LRESULT CUDProcsCommDlg::OnReadClose(WPARAM wParam,LPARAM lParam)
{
	//�Զ���Ĺر��뻺��������Ϣ
	CString str;
	switch (WSAGETSELECTEVENT(lParam))
	{
	    case FD_READ:
		if(recvfrom(ServerSocket,(char *)&msg,sizeof(msg),0,(LPSOCKADDR)&m_sockServerAddr,(int *)&socklen) == SOCKET_ERROR)		
		{
			list.AddString("����ʧ��!�Է�������Ӧ�ý���û������");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
//ADD
}
