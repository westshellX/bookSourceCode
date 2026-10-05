// UIThreadDemo2.h : main header file for the UITHREADDEMO2 application
//

#if !defined(AFX_UITHREADDEMO2_H__C315DBA4_3924_45E8_82AE_25B7A856E16F__INCLUDED_)
#define AFX_UITHREADDEMO2_H__C315DBA4_3924_45E8_82AE_25B7A856E16F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUIThreadDemo2App:
// See UIThreadDemo2.cpp for the implementation of this class
//

class CUIThreadDemo2App : public CWinApp
{
public:
	CUIThreadDemo2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUIThreadDemo2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUIThreadDemo2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UITHREADDEMO2_H__C315DBA4_3924_45E8_82AE_25B7A856E16F__INCLUDED_)
