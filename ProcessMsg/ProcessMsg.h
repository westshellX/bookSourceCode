// ProcessMsg.h : main header file for the PROCESSMSG application
//

#if !defined(AFX_PROCESSMSG_H__5982FF17_A89F_44ED_B99B_34A427F9E327__INCLUDED_)
#define AFX_PROCESSMSG_H__5982FF17_A89F_44ED_B99B_34A427F9E327__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProcessMsgApp:
// See ProcessMsg.cpp for the implementation of this class
//

class CProcessMsgApp : public CWinApp
{
public:
	CProcessMsgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessMsgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProcessMsgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSMSG_H__5982FF17_A89F_44ED_B99B_34A427F9E327__INCLUDED_)
