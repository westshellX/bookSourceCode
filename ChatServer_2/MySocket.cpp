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
void MySocket::GetDlg(CChatServerDlg *dlg)        //获得窗口界面的指针
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
	CAsyncSocket::OnClose(nErrorCode);
}

void MySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	m_dlg->OnReceive();
//ADD
	CAsyncSocket::OnReceive(nErrorCode);
}

void MySocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	if(m_dlg->m_ServerSocket==NULL)
		m_dlg->OnAccept();
//ADD
	CAsyncSocket::OnAccept(nErrorCode);
}
