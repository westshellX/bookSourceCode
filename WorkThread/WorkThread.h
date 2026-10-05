// WorkThread.h : main header file for the WORKTHREAD application
//

#if !defined(AFX_WORKTHREAD_H__74019543_4DFC_491B_BA41_B936D613EAF3__INCLUDED_)
#define AFX_WORKTHREAD_H__74019543_4DFC_491B_BA41_B936D613EAF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWorkThreadApp:
// See WorkThread.cpp for the implementation of this class
//

class CWorkThreadApp : public CWinApp
{
public:
	CWorkThreadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkThreadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWorkThreadApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKTHREAD_H__74019543_4DFC_491B_BA41_B936D613EAF3__INCLUDED_)
