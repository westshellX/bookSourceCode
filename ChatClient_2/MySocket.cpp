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
void MySocket::GetDlg(CChatClientDlg * dlg)            //��ô��ڽ����ָ��
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
	CAsyncSocket::OnClose(nErrorCode);
}

void MySocket::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	//ȷ�Ͽͻ����Ƿ�ɹ����ӵ�������
	if(nErrorCode)
	{
		AfxMessageBox("����ʧ�ܣ��������ԣ�");
		return;
	}
	 m_dlg->OnConnect();
//ADD
	CAsyncSocket::OnConnect(nErrorCode);
}

void MySocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	m_dlg->OnReceive();
//ADD
	CAsyncSocket::OnReceive(nErrorCode);
}
