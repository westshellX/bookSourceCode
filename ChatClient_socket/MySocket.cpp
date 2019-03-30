// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "MySocket.h"
//ADD
#include "ChatClientDlg.h"
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
void MySocket::GetDlg(CChatClientDlg *dlg)
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
