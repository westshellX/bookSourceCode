// MySocket.cpp : ʵ���ļ�
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


// MySocket ��Ա����

//ADD
void MySocket::GetDlg(CChatClientDlg *dlg)
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
