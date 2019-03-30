// ClientSocket.cpp : ʵ���ļ�
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


// CClientSocket ��Ա����

void CClientSocket::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	//ȷ�Ͽͻ����Ƿ�ɹ����ӵ�������
	if(nErrorCode)
	{
		AfxMessageBox("����ʧ�ܣ��������ԣ�");
		return;
	}
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString("���ӷ������ɹ���");
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);

	//��������
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->ServerIP.EnableWindow(false);
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->ServerPort.EnableWindow(false);
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ButtonConnect.EnableWindow(false);
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ButtonDisconnect.EnableWindow();
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_EditWords.EnableWindow();
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ButtonSend.EnableWindow();
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ButtonExit.EnableWindow(false);
	((CChatClientDlg*)(AfxGetApp()->m_pMainWnd))->m_ButtonClear.EnableWindow();
	//��������
//ADD
	CAsyncSocket::OnConnect(nErrorCode);
}
void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	char szTemp[200];
	int n=Receive(szTemp,200);
	szTemp[n]='\0';
	CString sTemp;
	sTemp.Format("�յ���%s",szTemp);
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString(sTemp);
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
		((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);
//ADD

	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
		((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.AddString("�������˶Ͽ���");
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.SetTopIndex(
		((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ListWords.GetCount()-1);
	Close();
	//��������
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->ServerIP.EnableWindow();
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->ServerPort.EnableWindow();
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonConnect.EnableWindow();
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonDisconnect.EnableWindow(false);
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_EditWords.EnableWindow(false);
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonSend.EnableWindow(false);
	((CChatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_ButtonExit.EnableWindow();
	//��������
//ADD

	CAsyncSocket::OnClose(nErrorCode);
}
