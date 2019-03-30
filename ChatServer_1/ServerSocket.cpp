// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ServerSocket.h"
//ADD
#include "ChatServerDlg.h"
//ADD


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数

void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	//关闭与客户端的通信信道
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString("客户端断开连接");
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);
	Close();//关闭与客户端通信的Socket

	//界面完善
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonDisconnect.EnableWindow(false);
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_EditWords.EnableWindow(false);
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonSend.EnableWindow(false);
	//界面完善

//ADD

	CAsyncSocket::OnClose(nErrorCode);
}

void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	//接收客户端发来的信息
	char szTemp[200];
	int n=Receive(szTemp,200);//接收信息
	szTemp[n]='\0';
    CString sTemp;
	sTemp.Format("收到：%s",szTemp);
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString(sTemp);//显示信息
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
		((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);
//ADD

	CAsyncSocket::OnReceive(nErrorCode);
}
