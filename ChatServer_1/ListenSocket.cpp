// ListenSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ListenSocket.h"
//ADD
#include "ChatServerDlg.h"
//ADD

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 成员函数

void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	// 接受客户端的连接请求
	Accept(((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ServerSocket);//接受连接请求
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ServerSocket.AsyncSelect(FD_READ|FD_CLOSE);
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString("接受了一个客户端的连接请求");
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
		((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);

	//界面完善
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonDisconnect.EnableWindow();
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_EditWords.EnableWindow();
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonSend.EnableWindow();
	//界面完善

//ADD

	CAsyncSocket::OnAccept(nErrorCode);
}
