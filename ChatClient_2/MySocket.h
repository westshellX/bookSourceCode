#pragma once

// MySocket ÃüÁîÄ¿±ê
//ADD
class CChatClientDlg;
//ADD
class MySocket : public CAsyncSocket
{
public:
	MySocket();
	virtual ~MySocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
//ADD
	CChatClientDlg * m_dlg;
	void GetDlg(CChatClientDlg * dlg);
//ADD
};


