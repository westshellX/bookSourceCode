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
void MySocket::GetDlg(CChatClientDlg * dlg)            //获得窗口界面的指针
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

void MySocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	//确认客户端是否成功连接到服务器
	if(nErrorCode)
	{
		AfxMessageBox("连接失败，请您重试！");
		return;
	}
	 m_dlg->OnConnect();
//ADD
	CAsyncSocket::OnConnect(nErrorCode);
}

void MySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	m_dlg->OnReceive();
//ADD
	CAsyncSocket::OnReceive(nErrorCode);
}
