// UDProcsComm.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDProcsCommApp:
// �йش����ʵ�֣������ UDProcsComm.cpp
//

class CUDProcsCommApp : public CWinApp
{
public:
	CUDProcsCommApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUDProcsCommApp theApp;