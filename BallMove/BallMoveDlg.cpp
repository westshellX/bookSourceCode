// BallMoveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BallMove.h"
#include "BallMoveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CBallMoveDlg dialog

CBallMoveDlg::CBallMoveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBallMoveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBallMoveDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Isblueball=m_Isredball=m_Isgreenball=false;
}

void CBallMoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBallMoveDlg)
	DDX_Control(pDX, IDC_GREENBALL, m_greenrect);
	DDX_Control(pDX, IDC_BLUEBALL, m_bluerect);
	DDX_Control(pDX, IDC_REDBALL, m_redrect);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBallMoveDlg, CDialog)
	//{{AFX_MSG_MAP(CBallMoveDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STAR, OnStar)
	ON_BN_CLICKED(IDC_STOPBLUE, OnStopblue)
	ON_BN_CLICKED(IDC_STOPGREEN, OnStopgreen)
	ON_BN_CLICKED(IDC_STOPRED, OnStopred)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBallMoveDlg message handlers

BOOL CBallMoveDlg::OnInitDialog()
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
	GetDlgItem(IDC_STOPBLUE)->EnableWindow(false);
	GetDlgItem(IDC_STOPRED)->EnableWindow(false);
	GetDlgItem(IDC_STOPGREEN)->EnableWindow(false);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBallMoveDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBallMoveDlg::OnPaint() 
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
	if(m_Isblueball)
	{
		CDC *pDC=m_bluerect.GetDC();
		CBrush *poldbrush;
		CBrush newbrush(RGB(0,0,255));
		poldbrush=pDC->SelectObject(&newbrush);
		pDC->Ellipse(blueball.pos,0,blueball.pos+blueball.rect.Height(),blueball.rect.Height());
		pDC->SelectObject(poldbrush);
		pDC->DeleteDC();
	}
	if(m_Isredball)
	{
		CDC *pDC=m_redrect.GetDC();
		CBrush *poldbrush;
		CBrush newbrush(RGB(255,0,0));
		poldbrush=pDC->SelectObject(&newbrush);
		pDC->Ellipse(redball.pos,0,redball.pos+redball.rect.Height(),redball.rect.Height());

		pDC->SelectObject(poldbrush);
		pDC->DeleteDC();
	}
	if(m_Isgreenball)
	{
		CDC * pDC=m_greenrect.GetDC();
		CBrush *poldbrush;
		CBrush newbrush(RGB(0,255,0));
		poldbrush=pDC->SelectObject(&newbrush);
		pDC->Ellipse(greenball.pos,0,greenball.pos+greenball.rect.Height(),greenball.rect.Height());
		pDC->SelectObject(poldbrush);
		pDC->DeleteDC();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBallMoveDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
DWORD WINAPI BallMove(LPVOID ballparameter)
{
	BOOL DIRECT=false;
	lpball temp=(lpball)ballparameter;
	while(true)
	{
		if((temp->pos)>=(temp->rect.right-temp->rect.Height()))
		{
			DIRECT=true;
		}
		if((temp->pos)<=temp->rect.left)
		{
			DIRECT=false;
		}
		if(DIRECT)
		{
			temp->pos--;
		}
		else
		{
			temp->pos++;
		}
		CRect rect(temp->pos + temp->realrect.left - 2, temp->realrect.top - 2, temp->pos + temp->realrect.left + temp->rect.Height() + 2, temp->realrect.bottom + 2);   //上下左右各扩大2像素矩形区域，避免出现残影
		InvalidateRect(temp->hwnd,rect,true);
		Sleep(temp->speed);
	}
}

void CBallMoveDlg::OnStar() 
{
	// TODO: Add your control notification handler code here
	DWORD ThreadID;
	DWORD code;
	CRect rect,rect1;
	GetClientRect(rect);
	ClientToScreen(rect);
	if(!m_Isredball)
	{
		m_redrect.GetClientRect(ballrect);
		m_redrect.GetClientRect(rect1);
		m_redrect.ClientToScreen(rect1);
		
		rect1-=rect.TopLeft();
		redball.hwnd=m_hWnd;
		redball.speed=10;
		redball.pos=ballrect.left;
		redball.rect=ballrect;
		redball.realrect=rect1;
		m_Isredball=true;
	}
	if(!GetExitCodeThread(redThread,&code)||(code!=STILL_ACTIVE))
	{
		redThread=CreateThread(NULL,0,BallMove,&redball,0,&ThreadID);
	}
	if(redThread==NULL)
	{
		MessageBox("线程创建失败!");
		m_Isredball=false;
	}
	if(!m_Isblueball)
	{
		m_bluerect.GetClientRect(ballrect);
		m_bluerect.GetClientRect(rect1);
		m_bluerect.ClientToScreen(rect1);

		rect1-=rect.TopLeft();
		blueball.hwnd=m_hWnd;
		blueball.speed=20;
		blueball.pos=ballrect.left;
		blueball.rect=ballrect;
		blueball.realrect=rect1;
		m_Isblueball=true;
	}
	if(!GetExitCodeThread(blueThread,&code)||(code!=STILL_ACTIVE))
	{
		blueThread=CreateThread(NULL,0,BallMove,&blueball,0,&ThreadID);
	}
	if(blueThread==NULL)
	{
		MessageBox("线程创建失败!");
		m_Isblueball=false;
	}
	if(!m_Isgreenball)
	{
		m_greenrect.GetClientRect(ballrect);
		m_greenrect.GetClientRect(rect1);
		m_greenrect.ClientToScreen(rect1);
		rect1-=rect.TopLeft();
		greenball.hwnd=m_hWnd;
		greenball.speed=10;
		greenball.pos=ballrect.left;
		greenball.rect=ballrect;
		greenball.realrect=rect1;
		m_Isgreenball=true;
	}
	if(!GetExitCodeThread(greenThread,&code)||(code!=STILL_ACTIVE))
	{
		greenThread=CreateThread(NULL,0,BallMove,&greenball,0,&ThreadID);
	}
	if(greenThread=NULL)
	{
		MessageBox("线程创建失败！");
		m_Isgreenball=false;
	}
	GetDlgItem(IDC_STAR)->EnableWindow(false);
	GetDlgItem(IDC_STOPBLUE)->EnableWindow(true);
	GetDlgItem(IDC_STOPRED)->EnableWindow(true);
	GetDlgItem(IDC_STOPGREEN)->EnableWindow(true);	
}


void CBallMoveDlg::OnStopblue() 
{
	// TODO: Add your control notification handler code here
	DWORD code;
	if(GetExitCodeThread(blueThread,&code))
	{
		if(code==STILL_ACTIVE)
		{
			TerminateThread(blueThread,0);
			CloseHandle(blueThread);
		}
	}
	GetDlgItem(IDC_STOPBLUE)->EnableWindow(false);
	GetDlgItem(IDC_STAR)->EnableWindow(true);
	
}

void CBallMoveDlg::OnStopgreen() 
{
	// TODO: Add your control notification handler code here
	DWORD code;
	if(GetExitCodeThread(greenThread,&code))
	{
		if(code==STILL_ACTIVE)
		{
			TerminateThread(greenThread,0);
			CloseHandle(greenThread);
		}
	}
	GetDlgItem(IDC_STOPGREEN)->EnableWindow(false);
	GetDlgItem(IDC_STAR)->EnableWindow(true);

	
}

void CBallMoveDlg::OnStopred() 
{
	// TODO: Add your control notification handler code here
	DWORD code;
	if(GetExitCodeThread(redThread,&code))
	{
		if(code==STILL_ACTIVE)
		{
			TerminateThread(redThread,0);
			CloseHandle(redThread);
		}
		GetDlgItem(IDC_STOPRED)->EnableWindow(false);
		GetDlgItem(IDC_STAR)->EnableWindow(true);
	}
	
}
