// GetIPAndPortDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GetIPAndPort.h"
#include "GetIPAndPortDlg.h"

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


// CGetIPAndPortDlg �Ի���




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


// CGetIPAndPortDlg ��Ϣ�������

BOOL CGetIPAndPortDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGetIPAndPortDlg::OnPaint()
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
HCURSOR CGetIPAndPortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGetIPAndPortDlg::OnShowIpAndPort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	BYTE nFild[4];			//�ֱ���IP���ĸ��ֶ�
	CString sip;            //IP��ַ���ַ�����ʽ������ֱ����ʾ�ڽ����ϵģ�
	UpdateData();           //ˢ�¶Ի�����棬��ȡ�û�����

	//��֤�����Ƿ�Ϸ�
	if(m_ip.IsBlank())      //���û�û����дIP����ʾ����д
	{
		AfxMessageBox("����дIP��ַ!");
		return;
	}

	if(strport.IsEmpty())	//���û������ƶ��˿ںţ�������ָ��
	{
		AfxMessageBox("��ָ�����̶˿�!");
		return;
	}

	//��ȡ�û������IP��ֵַ
	m_ip.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);

	//��IP��ַ��ʽ��Ϊ�����ڵ�����Ļ����ʾ���ַ���
	sip.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	//�ڽ�������ʾ�û������������̵�ַ����������������IP�Ͷ˿ڣ�
	m_showIpAndPort.SetWindowTextA(sip + " :" + strport);
	m_ip.SetFocus();		//����ص�IP��ַ��
}

void CGetIPAndPortDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlg;
	dlg.DoModal();			//��ʾ�����ڡ��Ի���
}
