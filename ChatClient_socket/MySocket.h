#pragma once

// MySocket ÃüÁîÄ¿±ê

//ADD
#include "Afxsock.h"
class CChatClientDlg;
//ADD

class MySocket : public CSocket
{
public:
	MySocket();
	virtual ~MySocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
//ADD
	CChatClientDlg * m_dlg;
	void GetDlg(CChatClientDlg * dlg);
//ADD
};


