// ThreadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProcessMsg.h"
#include "ThreadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThreadDlg dialog


CThreadDlg::CThreadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThreadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CThreadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThreadDlg)
	DDX_Control(pDX, IDC_LIST_THREAD, m_listctrlThread);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CThreadDlg, CDialog)
	//{{AFX_MSG_MAP(CThreadDlg)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadDlg message handlers

void CThreadDlg::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	OnOK();
	
}

BOOL CThreadDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listctrlThread.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listctrlThread.InsertColumn(1,_T("序号"),LVCFMT_CENTER,50,1);
	m_listctrlThread.InsertColumn(2,_T("线程ID"),LVCFMT_CENTER,100,1);
	m_listctrlThread.InsertColumn(3,_T("优先级"),LVCFMT_CENTER,80,1);
	CString csPID=((CProcessMsgDlg*)m_parent)->m_csPID;
	DWORD dwTID=atol(csPID);
	GetThreadInfo(dwTID);
	m_listctrlThread.SetTextBkColor(RGB(255,191,127));
	m_listctrlThread.SetTextColor(RGB(35,91,217));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CThreadDlg::GetThreadInfo(DWORD dwID)
{
	char Buffer[256];
	HANDLE hThreadSnap=NULL;
	BOOL bRet=false;
	THREADENTRY32 te32={0};
	hThreadSnap=CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);
	if(hThreadSnap==INVALID_HANDLE_VALUE)
	{
		return false;
	}
	te32.dwSize=sizeof(THREADENTRY32);
	int i=0;
	if(Thread32First(hThreadSnap,&te32))
	{
		do
		{
			if(te32.th32OwnerProcessID==dwProcessId)
			{
				itoa(i,Buffer,10);
				m_listctrlThread.InsertColumn(1,buffer);
				ltoa(te32.th32ThreadID,Buffer,10);

				m_listctrlThread.SetItemText(1,1,Buffer);
				ltoa(te32.tpBasePri,Buffer,10);
				m_listctrlThread.SetItemText(1,2,Buffer);
				i++;
			}
		}
		while(Thread32Next(hThreadSnap,&te32));
		bRet=true;
	}
	else
	{
		bRet=false;
	}
	CloseHandle(hThreadSnap);
	return bRet;
}
