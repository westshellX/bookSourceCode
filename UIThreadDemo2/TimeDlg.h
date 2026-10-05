#if !defined(AFX_TIMEDLG_H__58B2319A_A4C7_437C_AA06_49C36025A525__INCLUDED_)
#define AFX_TIMEDLG_H__58B2319A_A4C7_437C_AA06_49C36025A525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TimeDlg dialog

class TimeDlg : public CDialog
{
// Construction
public:
	int thetime;
	TimeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(TimeDlg)
	enum { IDD = IDD_TIMEDLG };
	CString	m_time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TimeDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEDLG_H__58B2319A_A4C7_437C_AA06_49C36025A525__INCLUDED_)
