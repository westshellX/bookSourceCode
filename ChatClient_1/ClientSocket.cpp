// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ClientSocket.h"
//ADD
#include "ChatClientDlg.h"
//ADD

// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 成员函数

void CClientSocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	//确认客户端是否成功连接到服务器
	if(nErrorCode)
	{
		AfxMessageBox("连接失败，请您重试！");
		return;
	}
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString("连接服务器成功！");
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);

	//界面完善
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->ServerIP.EnableWindow(false);
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->ServerPort.EnableWindow(false);
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ButtonConnect.EnableWindow(false);
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ButtonDisconnect.EnableWindow();
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_EditWords.EnableWindow();
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ButtonSend.EnableWindow();
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ButtonExit.EnableWindow(false);
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ButtonClear.EnableWindow();
	//界面完善
//ADD
	CAsyncSocket::OnConnect(nErrorCode);
}
void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	char szTemp[200];
	int n=Receive(szTemp,200);
	szTemp[n]='\0';
	CString sTemp;
	sTemp.Format("收到：%s",szTemp);
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString(sTemp);
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
		((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);
//ADD

	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
		((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString("服务器端断开了");
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
		((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);
	Close();
	//界面完善
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->ServerIP.EnableWindow();
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->ServerPort.EnableWindow();
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonConnect.EnableWindow();
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonDisconnect.EnableWindow(false);
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_EditWords.EnableWindow(false);
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonSend.EnableWindow(false);
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonExit.EnableWindow();
	//界面完善
//ADD

	CAsyncSocket::OnClose(nErrorCode);
}
