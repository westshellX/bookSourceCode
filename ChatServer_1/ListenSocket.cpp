// ListenSocket.cpp : ʵ���ļ�
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


// CListenSocket ��Ա����

void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	// ���ܿͻ��˵���������
	Accept(((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ServerSocket);//������������
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ServerSocket.AsyncSelect(FD_READ|FD_CLOSE);
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString("������һ���ͻ��˵���������");
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
		((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);

	//��������
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonDisconnect.EnableWindow();
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_EditWords.EnableWindow();
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonSend.EnableWindow();
	//��������

//ADD

	CAsyncSocket::OnAccept(nErrorCode);
}
