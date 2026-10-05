// ProcessMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProcessMsg.h"
#include "ProcessMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#pragma comment(lib,"psapi")
CString GetProcessPath(DWORD idProcess)
{
	CString csPath=_T("");
	HANDLE hProcess=OpenProcess(PROCWSS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,idProcess);
	if(NULL!=hProcess)
	{
		HMODLE hMod;
		DWORD cbNeeded;
		if(EnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeeded))
		{
			DWORD dw=GetModuleFileNameEx(hProcess,hMod,csPath.GetBuffer(MAX_PATH),MAX_PATH);
			csPath.ReleaseBuffer();
		}
		CloseHandle(hProcess);
	}
	return(csPath);
}
CString GetProcessPriority(HANDLE hProcess)
{
	char szNORMAL[10]=_T("NORMAL");
	char szIDLE[10]=_T("IDLE");
	char szREALTIME[10]=_T("REALTIME");
	char szHIGH[10]=_T("HIGH");
	char szNULL[10]=_T("NULL");

	switch(GetPriotrityClass(hProcess))
	{
	case NORMAL_PRIORITY_CLASS:
		return szNORMAL;
		break;
	case IDLE_PRIORITY_CLASS:
		return szIDLE;
		break;
	case REALTIME_PRIORITY_CLASS:
		return SZREALTIME;
		break;
	case HIGH_PRIORITY_CLASS:
		return szHIGH;
		break;
	default:
		return szNULL;
	}
}
void TerminateProcessID(DWORD dwID)
{
	HANDLE hProcess=NULL;
	hProcess=OpenProcess(PROCESS_TERMINATE,false,dwID);
	if(hProcess!=NULL)
	{
		TerminateProcess(hProcess,0);
		::CloseHandle(hProcess);
	}
}


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessMsgDlg dialog

CProcessMsgDlg::CProcessMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcessMsgDlg)
	m_nNumberofProcess = _T("");
	m_csHour = _T("");
	m_csMinute = _T("");
	m_csSecond = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcessMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessMsgDlg)
	DDX_Control(pDX, IDC_LIST_PROCESS, m_listctrlProcess);
	DDX_Text(pDX, IDC_STATIC_PROCESS_CNT, m_nNumberofProcess);
	DDX_Text(pDX, IDC_EDIT_HOUR, m_csHour);
	DDX_Text(pDX, IDC_EDIT_MINUTE, m_csMinute);
	DDX_Text(pDX, IDC_EDIT_SECOND, m_csSecond);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProcessMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CProcessMsgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEWPROCESS, OnButtonNewprocess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessMsgDlg message handlers

BOOL CProcessMsgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProcessMsgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProcessMsgDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProcessMsgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CProcessMsgDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}

void CProcessMsgDlg::OnButtonNewprocess() 
{
	// TODO: Add your control notification handler code here
	
}

void CProcessMsgDlg::DisplaySystemTime()
{

}

void CProcessMsgDlg::UpdateProcess()
{

}

void CProcessMsgDlg::Insert(CListCtrl m_l, CString str)
{

}

CString CProcessMsgDlg::GetProcessCreateTime(DWORD dwID, int i)
{

}
