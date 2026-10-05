// ModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProcessMsg.h"
#include "ModuleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModuleDlg dialog


CModuleDlg::CModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModuleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModuleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModuleDlg)
	DDX_Control(pDX, IDC_LIST_MODULE, m_listctrlModule);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModuleDlg, CDialog)
	//{{AFX_MSG_MAP(CModuleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModuleDlg message handlers

void CModuleDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

int CModuleDlg::GetModuleMsg(DWORD dwID)
{
	MODULEENTRY32 me32;
	me32.dwSize=sizeof(MODULEENTRY32);
	HANDLE hModuleSnap;

	hModuleSnap=::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,dwID);
	if(hModuleSnap==INVALID_HANDLE_VALUE)
	{
		return false;
	}
	BOOL bRet=::Module32First(hModuleSnap,&me32);
	while(bRet)
	{
		char szMod[56];
		wsprintf(szMod,"%u",me32.th32ModuleID);
		m_listctrlModule.InsertItem(1,me32.szModule);
		m_listctrlModule.SetItemText(1,1,szMod);

		bRet=::Module32Next(hModuleSnap,&me32);
	}
	::CloseHandle(hModuleSnap);
	return 0;

	


}

CString CModuleDlg::GetProcessModule(DWORD dwID)
{

	HMODULE hMod[1024];
	char Buffer[256];
	 
	HANDLE hProcess;
	DWORD cbNeed;
	unsigned int i;
	char szModName[MAX_PATH];
	m_listctrlModule.DeleteAllItems();
	hProcess=::OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,dwID);
	if(hProcess && EnumProcessModules(hProcess,hMod,sizeof(hMod),&cbNeed))
	{
		for(i=0;i<=(cbNeed/sizeof(HMODLE));i++)
		{
			if(GetModuleFileNameEx(hProcess,hMod[i],szModName,sizeof(szModeName)))
			{
				m_listctrlModule.InsertItem(1,szModName);
				wsprintf(Buffer,"0x%08x",hMod[i]);
				m_listctrlModule.SetItemText(1,1,Buffer);
			}
		}
		CloseHandle(hProcess);
		return true;
	}
	else
	{
		CloseHandle(hProcess);
		return NULL;
	}

}

BOOL CModuleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listctrlModule.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listctrlModule.InsertColumn(1,_T("Ä£¿éÃû³Æ"),LVCFMT_CENTER,200,1);
	m_listctrlModule.InsertColumn(2,_T("Ä£¿éID"),LVCFMT_CENTER,100,1);
	CString csCID=((CProcessMgDlg*)m_parent)->m_csCID;
	m_listctrlModule.SetTextBkColor(RGB(255,191,127));
	m_listctrlModule.SetTextColor(RGB(35,91,217));

	DWORD dwCID=atol(csCID);
	GetProcessModule(dwCID);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
