// ServerSocket.cpp : ʵ���ļ�
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


// CServerSocket ��Ա����

void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	//�ر���ͻ��˵�ͨ���ŵ�
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString("�ͻ��˶Ͽ�����");
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);
	Close();//�ر���ͻ���ͨ�ŵ�Socket

	//��������
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonDisconnect.EnableWindow(false);
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_EditWords.EnableWindow(false);
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonSend.EnableWindow(false);
	//��������

//ADD

	CAsyncSocket::OnClose(nErrorCode);
}

void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	//���տͻ��˷�������Ϣ
	char szTemp[200];
	int n=Receive(szTemp,200);//������Ϣ
	szTemp[n]='\0';
    CString sTemp;
	sTemp.Format("�յ���%s",szTemp);
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString(sTemp);//��ʾ��Ϣ
	((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
		((CChatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);
//ADD

	CAsyncSocket::OnReceive(nErrorCode);
}
