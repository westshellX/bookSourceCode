//ADD
#include "SelfRoomDlg.h"
//ADD
#pragma once

// CClientSocket ÃüÁîÄ¿±ê

class CClientSocket : public CSocket
{
//ADD
public:
	CPtrList *clist;
	CSelfRoomDlg *m_dlgServer;
//ADD
public:
	CClientSocket();
//ADD
	CClientSocket(CPtrList *list);
//ADD
	virtual ~CClientSocket();
//ADD
public:
	CString m_strName;
//ADD
//	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


