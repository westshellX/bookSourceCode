// GetIPAndPort.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGetIPAndPortApp:
// �йش����ʵ�֣������ GetIPAndPort.cpp
//

class CGetIPAndPortApp : public CWinApp
{
public:
	CGetIPAndPortApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGetIPAndPortApp theApp;