#if !defined(AFX_TIMEDLG_H__E6A1D74D_BF57_49F2_B81B_234FC7577887__INCLUDED_)
#define AFX_TIMEDLG_H__E6A1D74D_BF57_49F2_B81B_234FC7577887__INCLUDED_

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

#endif // !defined(AFX_TIMEDLG_H__E6A1D74D_BF57_49F2_B81B_234FC7577887__INCLUDED_)
