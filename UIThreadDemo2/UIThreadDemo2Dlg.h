// UIThreadDemo2Dlg.h : header file
//

#if !defined(AFX_UITHREADDEMO2DLG_H__88622727_F56F_49EB_B782_AC550D97A5BD__INCLUDED_)
#define AFX_UITHREADDEMO2DLG_H__88622727_F56F_49EB_B782_AC550D97A5BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUIThreadDemo2Dlg dialog

class CUIThreadDemo2Dlg : public CDialog
{
// Construction
public:
	CUIThreadDemo2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUIThreadDemo2Dlg)
	enum { IDD = IDD_UITHREADDEMO2_DIALOG };
	CProgressCtrl	m_calprogress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUIThreadDemo2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUIThreadDemo2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONStar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UITHREADDEMO2DLG_H__88622727_F56F_49EB_B782_AC550D97A5BD__INCLUDED_)
