// P2PTalker.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CP2PTalkerApp:
// �йش����ʵ�֣������ P2PTalker.cpp
//

class CP2PTalkerApp : public CWinApp
{
public:
	CP2PTalkerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CP2PTalkerApp theApp;