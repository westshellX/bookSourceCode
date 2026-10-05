#if !defined(AFX_MODULEDLG_H__14AF78E5_E360_4336_A438_542585F2F7D6__INCLUDED_)
#define AFX_MODULEDLG_H__14AF78E5_E360_4336_A438_542585F2F7D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModuleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModuleDlg dialog

class CModuleDlg : public CDialog
{
// Construction
public:
	CDialog *m_parent;
	CModuleDlg(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CModuleDlg)
	enum { IDD = IDD_DIALOG_MODULE };
	CListCtrl	m_listctrlModule;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModuleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModuleDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString GetProcessModule(DWORD dwID);
	int GetModuleMsg(DWORD dwID);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODULEDLG_H__14AF78E5_E360_4336_A438_542585F2F7D6__INCLUDED_)
