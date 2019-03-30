// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__050163ED_11E0_4E4B_9610_44F23335EA8A__INCLUDED_)
#define AFX_CLIENTDLG_H__050163ED_11E0_4E4B_9610_44F23335EA8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Mysocket.h"

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog
class CMysocket;

class CClientDlg : public CDialog
{
// Construction
public:
	void ReceiveData();
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

	CMysocket* pMysocket;

	CString m_name;

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	CListBox	m_list;
	CEdit	m_info;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__050163ED_11E0_4E4B_9610_44F23335EA8A__INCLUDED_)
