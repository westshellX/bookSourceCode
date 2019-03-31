// ClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SelfChat.h"
#include "ClientSocket.h"
//ADD
#include "SelfChatDlg.h"
#include "tagHeader.h"
//ADD


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket ��Ա����

void CClientSocket::GetDlg(CSelfChatDlg *dlg)            //��ô��ڽ����ָ��
{
	    chatDlg = dlg;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	char buff[sizeof(Header)];
	memset(buff,0,sizeof(buff));
	Receive(buff,sizeof(buff));
	this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	Header *header = (Header*)buff;
	int length = header->len;
	char type = header->type;
	
	if(type == SEND_MESSAGE)
	{
		chatDlg->GetMsgFromRoom();
	}
	if(type == LOGIN_IO)
	{
		//chatDlg->m_UserList.ResetContent();
		chatDlg->UpdateUser();		
	}
//ADD

	CSocket::OnReceive(nErrorCode);
}
