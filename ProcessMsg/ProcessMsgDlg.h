// ProcessMsgDlg.h : header file
//

#if !defined(AFX_PROCESSMSGDLG_H__7DD627A9_A5FE_4073_8C03_EFC6B85AA6B7__INCLUDED_)
#define AFX_PROCESSMSGDLG_H__7DD627A9_A5FE_4073_8C03_EFC6B85AA6B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProcessMsgDlg dialog

class CProcessMsgDlg : public CDialog
{
// Construction
public:
	CString m_csPID;
	CString m_csCID;
	CProcessMsgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProcessMsgDlg)
	enum { IDD = IDD_PROCESSMSG_DIALOG };
	CListCtrl	m_listctrlProcess;
	CString	m_nNumberofProcess;
	CString	m_csHour;
	CString	m_csMinute;
	CString	m_csSecond;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessMsgDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProcessMsgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonNewprocess();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char szID[56];
	CSatusBarCtrl m_statusbar;
	CString GetProcessCreateTime(DWORD dwID,int i);
	void Insert(CListCtrl m_l,CString str);
	void UpdateProcess();
	void DisplaySystemTime();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSMSGDLG_H__7DD627A9_A5FE_4073_8C03_EFC6B85AA6B7__INCLUDED_)
