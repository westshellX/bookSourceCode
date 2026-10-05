// TimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UIThreadDemo1.h"
#include "TimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TimeDlg dialog


TimeDlg::TimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(TimeDlg)
	m_time = _T("");
	//}}AFX_DATA_INIT
	thetime=0;
}


void TimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TimeDlg)
	DDX_Text(pDX, IDC_EDIT_TIME, m_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TimeDlg, CDialog)
	//{{AFX_MSG_MAP(TimeDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TimeDlg message handlers

void TimeDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	thetime++;
	m_time.Format("timer is: %d",thetime);
	UpdateData(false);
	
	CDialog::OnTimer(nIDEvent);
}

BOOL TimeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetTimer(1,500,NULL);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
