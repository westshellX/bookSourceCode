#pragma once

// CServerSocket ����Ŀ��

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
//ADD
	CPtrList connectList;
//ADD
	virtual void OnAccept(int nErrorCode);
};


