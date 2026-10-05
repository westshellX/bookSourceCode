// WorkThreadDlg.h : header file
//

#if !defined(AFX_WORKTHREADDLG_H__B44CCAA2_7756_45BD_B405_EF152FCA5241__INCLUDED_)
#define AFX_WORKTHREADDLG_H__B44CCAA2_7756_45BD_B405_EF152FCA5241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWorkThreadDlg dialog
struct ProgressInfo
{
	UINT nstar;
	CProgressCtrl *pctrlProgress;
	HWND hwnd;
};


class CWorkThreadDlg : public CDialog
{
// Construction
public:
	CWorkThreadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkThreadDlg)
	enum { IDD = IDD_WORKTHREAD_DIALOG };
	CProgressCtrl	m_calprogress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkThreadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	ProgressInfo info;
	CWinThread *pThread;

	// Generated message map functions
	//{{AFX_MSG(CWorkThreadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStar();
	afx_msg void OnStop();
	afx_msg void OnGoon();
	afx_msg void OnMsg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKTHREADDLG_H__B44CCAA2_7756_45BD_B405_EF152FCA5241__INCLUDED_)
