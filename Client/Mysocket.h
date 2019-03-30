#if !defined(AFX_MYSOCKET_H__37CC683E_82B0_44FE_A7F8_26E66A6A5831__INCLUDED_)
#define AFX_MYSOCKET_H__37CC683E_82B0_44FE_A7F8_26E66A6A5831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mysocket.h : header file
//
#include "Afxsock.h"
#include "ClientDlg.h"

class CClientDlg ;

class CMysocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CMysocket(CClientDlg* pDlg);
	virtual ~CMysocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMysocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CClientDlg* pClientdlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__37CC683E_82B0_44FE_A7F8_26E66A6A5831__INCLUDED_)
