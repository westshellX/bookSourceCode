#if !defined(AFX_THREADDLG_H__0E786437_B93D_4CE8_BF9B_903DB6C4D5AB__INCLUDED_)
#define AFX_THREADDLG_H__0E786437_B93D_4CE8_BF9B_903DB6C4D5AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThreadDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThreadDlg dialog

class CThreadDlg : public CDialog
{
// Construction
public:
	BOOL GetThreadInfo(DWORD dwID);
	CThreadDlg(CWnd* pParent = NULL);   // standard constructor

	CDialog *m_parent;


// Dialog Data
	//{{AFX_DATA(CThreadDlg)
	enum { IDD = IDD_DIALOG_THREAD };
	CListCtrl	m_listctrlThread;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThreadDlg)
	afx_msg void OnButtonOk();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREADDLG_H__0E786437_B93D_4CE8_BF9B_903DB6C4D5AB__INCLUDED_)
