// UIThreadDemo1Dlg.h : header file
//

#if !defined(AFX_UITHREADDEMO1DLG_H__E99BFB1A_6DE5_4DD0_B689_4D7C49255C0E__INCLUDED_)
#define AFX_UITHREADDEMO1DLG_H__E99BFB1A_6DE5_4DD0_B689_4D7C49255C0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUIThreadDemo1Dlg dialog

class CUIThreadDemo1Dlg : public CDialog
{
// Construction
public:
	CUIThreadDemo1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUIThreadDemo1Dlg)
	enum { IDD = IDD_UITHREADDEMO1_DIALOG };
	CProgressCtrl	m_calprogress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUIThreadDemo1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUIThreadDemo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStar();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UITHREADDEMO1DLG_H__E99BFB1A_6DE5_4DD0_B689_4D7C49255C0E__INCLUDED_)
