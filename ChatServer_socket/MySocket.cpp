// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "MySocket.h"
//ADD
#include "ChatServerDlg.h"
//ADD

// MySocket

MySocket::MySocket()
{
}

MySocket::~MySocket()
{
}


// MySocket 成员函数

//ADD
void MySocket::GetDlg(CChatServerDlg *dlg)
{
	m_dlg=dlg;
}
//ADD

void MySocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	m_dlg->OnClose();
//ADD
	CSocket::OnClose(nErrorCode);
}

void MySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	m_dlg->OnReceive();
	AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
//ADD
	CSocket::OnReceive(nErrorCode);
}

void MySocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	if(m_dlg->m_ServerSocket==NULL)
		m_dlg->OnAccept();
//ADD
	CSocket::OnAccept(nErrorCode);
}
