#pragma once

// CClientSocket ����Ŀ��
//ADD
class CSelfChatDlg;
//ADD

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
//ADD
	CSelfChatDlg *chatDlg;
	CString m_strName;
	void GetDlg(CSelfChatDlg *dlg);
//ADD
	virtual void OnReceive(int nErrorCode);
};


