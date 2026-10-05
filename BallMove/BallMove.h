// BallMove.h : main header file for the BALLMOVE application
//

#if !defined(AFX_BALLMOVE_H__C22CF6AE_C243_45FA_B9F3_9D9E7351B6D6__INCLUDED_)
#define AFX_BALLMOVE_H__C22CF6AE_C243_45FA_B9F3_9D9E7351B6D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBallMoveApp:
// See BallMove.cpp for the implementation of this class
//

class CBallMoveApp : public CWinApp
{
public:
	CBallMoveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBallMoveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBallMoveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BALLMOVE_H__C22CF6AE_C243_45FA_B9F3_9D9E7351B6D6__INCLUDED_)
