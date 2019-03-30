// MySocket.cpp : ʵ���ļ�
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


// MySocket ��Ա����

//ADD
void MySocket::GetDlg(CChatServerDlg *dlg)
{
	m_dlg=dlg;
}
//ADD

void MySocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	m_dlg->OnClose();
//ADD
	CSocket::OnClose(nErrorCode);
}

void MySocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	m_dlg->OnReceive();
	AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
//ADD
	CSocket::OnReceive(nErrorCode);
}

void MySocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	if(m_dlg->m_ServerSocket==NULL)
		m_dlg->OnAccept();
//ADD
	CSocket::OnAccept(nErrorCode);
}
