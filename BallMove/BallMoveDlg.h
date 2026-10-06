// BallMoveDlg.h : header file
//

#if !defined(AFX_BALLMOVEDLG_H__7FCB0C69_E176_4156_B0E1_83ECE63F0DEC__INCLUDED_)
#define AFX_BALLMOVEDLG_H__7FCB0C69_E176_4156_B0E1_83ECE63F0DEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBallMoveDlg dialog

typedef struct ballinfo{
	HWND hwnd;
	int speed;
	int pos;
	CRect rect;     //长方形矩形区域，采用Height()表示ball的直径
	CRect realrect;
}theball,*lpball;

class CBallMoveDlg : public CDialog
{
// Construction
public:
	CBallMoveDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBallMoveDlg)
	enum { IDD = IDD_BALLMOVE_DIALOG };
	CStatic	m_greenrect;
	CStatic	m_bluerect;
	CStatic	m_redrect;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBallMoveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CRect ballrect;
	
	theball greenball;
	theball redball;
	theball blueball;

	HANDLE greenThread;
	HANDLE redThread;
	HANDLE blueThread;

	BOOL m_Isblueball;
	BOOL m_Isredball;
	BOOL m_Isgreenball;

	// Generated message map functions
	//{{AFX_MSG(CBallMoveDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStar();
	afx_msg void OnStopblue();
	afx_msg void OnStopgreen();
	afx_msg void OnStopred();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BALLMOVEDLG_H__7FCB0C69_E176_4156_B0E1_83ECE63F0DEC__INCLUDED_)
