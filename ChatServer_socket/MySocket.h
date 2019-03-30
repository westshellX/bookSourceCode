#pragma once

// MySocket ÃüÁîÄ¿±ê
//ADD
#include "Afxsock.h"
class CChatServerDlg;
//ADD
class MySocket : public CSocket
{
public:
	MySocket();
	virtual ~MySocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
//ADD
	CChatServerDlg * m_dlg;
	void GetDlg(CChatServerDlg * dlg);
//ADD
};


