// P2PTalkerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "P2PTalker.h"
#include "P2PTalkerDlg.h"

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


// CP2PTalkerDlg �Ի���




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
	ON_MESSAGE(WM_CLIENT_READCLOSE,OnReadMsg)                //һ��Ҫ�������Ϣӳ�䣬�����޷�������Ϣ
//ADD
ON_BN_CLICKED(IDC_BUTTON1, &CP2PTalkerDlg::OnLogout)
ON_BN_CLICKED(IDC_BUTTON5, &CP2PTalkerDlg::OnSend)
ON_BN_CLICKED(IDC_BUTTON4, &CP2PTalkerDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CP2PTalkerDlg ��Ϣ�������

BOOL CP2PTalkerDlg::OnInitDialog()
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
	rstUsrCont = 0;
	onlUsrCont = 0;

	//����
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CP2PTalkerDlg::OnPaint()
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
HCURSOR CP2PTalkerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CP2PTalkerDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	//������֤
	UpdateData();
	if(LocaIP.IsBlank())
	{
		AfxMessageBox("�����ñ���IP��ַ!");
		return;	
	}
	if(locaPort.IsEmpty())
	{
		AfxMessageBox("��ָ��ͨ�Ŷ˿ں�!");
		return;
	}

	//��ʼ���׽������
    WSADATA wsaData;
    int iErrorCode;
    if (WSAStartup(MAKEWORD(2,1),&wsaData))         //����Windows Sockets DLL
	{
		m_MessageList.ReplaceSel("Winsock�޷���ʼ��!\r\n");
        WSACleanup();
        return;
	}
	m_MessageList.ReplaceSel("��ʼ����Socket��\r\n");
	SelfRcvSocket = socket(PF_INET,SOCK_DGRAM,0);    //�����������̵�Socket������ΪSOCK_DGRAM�������ӵ�ͨ��
    if(SelfRcvSocket == INVALID_SOCKET)
	{
		m_MessageList.ReplaceSel("����socketʧ��!\r\n");
        return;
	}

	//��ȡ�������̵�IP�Ͷ˿�
	BYTE nFild[4];
	CString sIP;
	LocaIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
    m_sockSelfRcvAddr.sin_family = AF_INET;
    m_sockSelfRcvAddr.sin_addr.S_un.S_addr = inet_addr(sIP); 
    m_sockSelfRcvAddr.sin_port = htons(atoi(locaPort));

	//���׽����뱾�����̰�
    if(bind(SelfRcvSocket,(LPSOCKADDR)&m_sockSelfRcvAddr,sizeof(m_sockSelfRcvAddr)) == SOCKET_ERROR)
    {
		m_MessageList.ReplaceSel("��ʧ��!\r\n");
        return;
	}
	iErrorCode = WSAAsyncSelect(SelfRcvSocket,m_hWnd,WM_CLIENT_READCLOSE,FD_READ);
    if (iErrorCode == SOCKET_ERROR) 
	{
		m_MessageList.ReplaceSel("WSAAsyncSelect�趨ʧ��!�������������������Ϣ\r\n");
        return;
	}
 	m_MessageList.ReplaceSel("�������������ɹ�!\r\n");
	m_MessageList.ReplaceSel("��ַ " + sIP + "  �˿� " + locaPort);
	this->SetWindowTextA("�������̣�" + sIP + ":" + locaPort + "���������С� - ptopTalker");
	
	//����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	//������ֹͣ����ʱ����SOCKET���
	m_MessageList.ReplaceSel("\r\n���ڹر�Socket��\r\n");
	closesocket(SelfRcvSocket);
	WSACleanup();
	m_MessageList.ReplaceSel("��������ֹͣ����!\r\n");
	this->SetWindowTextA("ptopTalker");

	//����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	//������֤
	UpdateData();
	if(nickname.IsEmpty())
	{
		AfxMessageBox("���Լ�ȡ���ǳư�!");
		return;
	}
	if(SevrIP.IsBlank())
	{
		AfxMessageBox("����дѡ��P2P������������IP��ַ!");
		return;	
	}
	if(sevrPort.IsEmpty())
	{
		AfxMessageBox("��ָ��P2P������̵Ķ˿�!");
		return;
	}

	BYTE nFild[4];
	CString sIP;
	//���ɵ�¼ע�ᱨ��
	LocaIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	RegisterAddr = "RGST_ADDR;";
	RegisterAddr += nickname + "," + sIP;
	RegisterAddr += ":" + locaPort;

	//��ȡP2P������̵�IP�Ͷ˿�
	SevrIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);	
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	//���ͱ���
	this->StartSndSocket(RegisterAddr,sIP,sevrPort);
	this->SetWindowTextA("�ѵ�¼P2P��������" + sIP + ":" + sevrPort + "�� - ptopTalker");

	//����
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
	//����������ϵͳ��������Ϣ
	CString str,strHead,strData;
	switch (WSAGETSELECTEVENT(lParam))
	{
	    case FD_READ:
		socklen = sizeof(m_sockSelfRcvAddr);
		recvfrom(SelfRcvSocket,(char *)&msgbuf,sizeof(msgbuf),0,(LPSOCKADDR)&m_sockSelfRcvAddr,(int *)&socklen);
		WSAAsyncSelect(SelfRcvSocket,m_hWnd,WM_CLIENT_READCLOSE,FD_READ);
		str.Format("%s",msgbuf.msg);

		//��ȡ����ͷ�����ݲ���
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
	//�ӱ����н�ȡ�ǳ��ֶ�
	n = strMsgData.Find(",");
	usrname = strMsgData.Left(n);
	strMsgData = strMsgData.Right(strMsgData.GetLength() - (n + 1));
	//���ν�ȡIP�Ͷ˿ڸ����ֶ�
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

	//���濪ʼ�����û��ǼǴ���
	BOOL BePresnc = false;              //ָʾ����û��Ƿ����ڷ�������ע��
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
				//���û�����ʱ�ı���IP����������ע����û���ϢҲ������ͬ������
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

	//�����û���������Ϊ���Դ���
	m_UserList.EnableWindow(true);
	m_UserList.ResetContent();
	m_MessageList.SetWindowTextA("");
	OnlUsrInfo = "UPDT_USR;";
	for(int i = 0;i < rstUsrCont;i++)
	{
		if(rstUsr[i].onlStat)
		{
			OnlUsrInfo += CString(rstUsr[i].usrname) + "&";                    //���ɸ����û��౨��
			m_UserList.AddString(CString(rstUsr[i].usrname));

			CString sIP,sP,onlUsrStateView;
			sIP.Format("%d.%d.%d.%d",rstUsr[i].ipFild[0],rstUsr[i].ipFild[1],rstUsr[i].ipFild[2],rstUsr[i].ipFild[3]);
			sP.Format("%d",rstUsr[i].port);
			onlUsrStateView = CString(rstUsr[i].usrname) + " -IP:";
			onlUsrStateView += sIP + " �˿�:";
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
	//���Դ���
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
	//�ӱ����н�ȡ�ǳ��ֶ�
	n = strMsgData.Find(",");
	usrname = strMsgData.Left(n);
	strMsgData = strMsgData.Right(strMsgData.GetLength() - (n + 1));

	//�ڱ��ط������������û������IP��ַ
	for(int i = 0;i < rstUsrCont;i++)
	{
		if(CString(rstUsr[i].usrname) == usrname)
		{
			//�ҵ�ƥ����û�֮����װ��P2P������Ӧ����
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
	//��ȡ�������ߵ�IP�Ͷ˿�
	n = strMsgData.Find(":");
	ip = strMsgData.Left(n);
	port = strMsgData.Right(strMsgData.GetLength() - (n + 1));

	//���û�������Ӧ����
	this->StartSndSocket(PtoPsrvRspse,ip,port);
}
//ADD

//ADD
void CP2PTalkerDlg::SendMsgtoPer(CString strMsgData)
{
	CString ip,port;
	int n;
	//�ӱ����н������Է���ַ��Ϣ
	n = strMsgData.Find(",");
	strMsgData = strMsgData.Right(strMsgData.GetLength() - (n + 1));
	//��ȡ�Է���IP�Ͷ˿�
	n = strMsgData.Find(":");
	ip = strMsgData.Left(n);
	port = strMsgData.Right(strMsgData.GetLength() - (n + 1));

	//��װ��Я��������Ϣ����Ϣ
	UpdateData();
	if(strMessage == "")
	{
		AfxMessageBox("���ܷ��Ϳ���Ϣ!");
		m_EditWords.SetFocus();
		return;
	}
	CTime time = CTime::GetCurrentTime();
	CString t = time.Format("%H:%M:%S");
	MsgTalktoPeer = "SND_MSG;" + nickname + ",";	
	MsgTalktoPeer += t + "\r\n   " + strMessage + "\r\n";

	//��Է�����������Ϣ
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
	//�ӱ�����ȡ���ǳƺ�������Ϣ�ֶ�
	n = strMsgData.Find(",");
	usrname = strMsgData.Left(n);
	MsgfrmPer = strMsgData.Right(strMsgData.GetLength() - (n + 1));

	//����������ʾ
	str = "\r\n" + usrname + "   " + MsgfrmPer;
	m_MessageList.ReplaceSel(str);
}
//ADD

void CP2PTalkerDlg::OnLogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	UpdateData();
	BYTE nFild[4];
	CString sIP;

	//���ɵ�¼ע�ᱨ��
	LocaIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	RegisterAddr = "RGST_ADDR;";
	RegisterAddr += nickname + "," + sIP;
	RegisterAddr += ":" + locaPort;

	//��ȡP2P������̵�IP�Ͷ˿�
	SevrIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);	
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	//���ͱ���
	this->StartSndSocket(RegisterAddr,sIP,sevrPort);
	m_UserList.ResetContent();
	this->SetWindowTextA("ע���ɹ�! - ptopTalker");

	//����
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
	//����һ��ר�����ڷ���Ϣ��Socket����
	SelfSndSocket = socket(PF_INET,SOCK_DGRAM,0);
    if(SelfSndSocket == INVALID_SOCKET)
	{
		m_MessageList.ReplaceSel("����socketʧ��!\r\n");
        return;
	}
    m_sockSelfSndAddr.sin_family = AF_INET;
    m_sockSelfSndAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 
    m_sockSelfSndAddr.sin_port = htons(8888);
    if(bind(SelfSndSocket,(LPSOCKADDR)&m_sockSelfSndAddr,sizeof(m_sockSelfSndAddr)) == SOCKET_ERROR)
    {
		m_MessageList.ReplaceSel("��ʧ��!\r\n");
        return;
	}

	//���÷��Ͳ���
	m_sockAddrto.sin_family = AF_INET;
    m_sockAddrto.sin_addr.S_un.S_addr = inet_addr(sIP); 
    m_sockAddrto.sin_port = htons(atoi(sPort));
	strcpy(msgbuf.msg,(LPCTSTR)msgtoSnd);
	msgbuf.i = 0;

	//����
	if(sendto(SelfSndSocket,(char *)&msgbuf,sizeof(msgbuf),0,(LPSOCKADDR)&m_sockAddrto,sizeof(m_sockAddrto)) == SOCKET_ERROR)
	{
		m_MessageList.ReplaceSel("��������ʧ��!\r\n");
	}
	closesocket(SelfSndSocket);   //����Ϣ���׽����������Ҫ��ʱ�رգ��Ա�������ϵͳ����Ҳ����ʱ����ʹ����
}

void CP2PTalkerDlg::OnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	//ѡ��Է��û���
	int nSel;
	nSel = m_UserList.GetCurSel();
	if(nSel == LB_ERR)
	{
		AfxMessageBox("���ȴ������û��б���ѡ��Է�����!");
		return;
	}
	CString UsrSel;
	m_UserList.GetText(nSel,UsrSel);
	UpdateData();
	if(UsrSel == nickname)
	{
		AfxMessageBox("������������Ϣ!");
		return;
	}
	//��������P2P������ı���
	BYTE nFild[4];
	CString sIP;
	LocaIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	PtoPsrvReqst = "REQ_ADDR;";
	PtoPsrvReqst += UsrSel + "," + sIP;
	PtoPsrvReqst += ":" + locaPort;

	//��ȡP2P������̵�IP�Ͷ˿�
	SevrIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);	
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	//���ͱ���
	this->StartSndSocket(PtoPsrvReqst,sIP,sevrPort);
//ADD
}

void CP2PTalkerDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
//ADD
}
