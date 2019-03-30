#if !defined(AFX_CLIENTSOCKET_H__EBCCDECD_5376_4D2A_8150_A7A7004B5DA9__INCLUDED_)
#define AFX_CLIENTSOCKET_H__EBCCDECD_5376_4D2A_8150_A7A7004B5DA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//
#include "ServerDlg.h"
#include "afxsock.h"

class CServerDlg;

/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CClientSocket(CServerDlg* pdlg);
	virtual ~CClientSocket();
	CServerDlg* m_pDlg;

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__EBCCDECD_5376_4D2A_8150_A7A7004B5DA9__INCLUDED_)
