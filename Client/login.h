#if !defined(AFX_LOGIN_H__C1643E9A_1002_4CE5_A99F_810F73146931__INCLUDED_)
#define AFX_LOGIN_H__C1643E9A_1002_4CE5_A99F_810F73146931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// login.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// login dialog

class login : public CDialog
{
// Construction
public:
	login(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(login)
	enum { IDD = IDD_LOGIN_DIALOG };
	CString	m_name;
	UINT	m_port;
	CString	m_servername;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(login)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(login)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__C1643E9A_1002_4CE5_A99F_810F73146931__INCLUDED_)
