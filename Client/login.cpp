// login.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// login dialog


login::login(CWnd* pParent /*=NULL*/)
	: CDialog(login::IDD, pParent)
{
	//{{AFX_DATA_INIT(login)
	m_name = _T("");
	m_port = 0;
	m_servername = _T("");
	//}}AFX_DATA_INIT
}


void login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(login)
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_port);
	DDX_Text(pDX, IDC_EDIT3, m_servername);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(login, CDialog)
	//{{AFX_MSG_MAP(login)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// login message handlers

void login::OnClose() 
{

	CDialog::OnClose();
}

BOOL login::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_servername = "localhost";
	m_port = 5000;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
