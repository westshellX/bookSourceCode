// UIThreadDemo1.h : main header file for the UITHREADDEMO1 application
//

#if !defined(AFX_UITHREADDEMO1_H__CFD8AA6B_4F7D_438A_AC25_1AA874E5ADB9__INCLUDED_)
#define AFX_UITHREADDEMO1_H__CFD8AA6B_4F7D_438A_AC25_1AA874E5ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUIThreadDemo1App:
// See UIThreadDemo1.cpp for the implementation of this class
//

class CUIThreadDemo1App : public CWinApp
{
public:
	CUIThreadDemo1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUIThreadDemo1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUIThreadDemo1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UITHREADDEMO1_H__CFD8AA6B_4F7D_438A_AC25_1AA874E5ADB9__INCLUDED_)
