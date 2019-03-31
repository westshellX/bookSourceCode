// P2PTalkerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//ADD
#include "rgstdUsr.h"
#include "stdafx.h"
#include "MyMsg.h"
//ADD


// CP2PTalkerDlg �Ի���
class CP2PTalkerDlg : public CDialog
{
// ����
public:
	CP2PTalkerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_P2PTALKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//ADD
	LRESULT OnReadMsg(WPARAM wParam,LPARAM lParam);                  //���ڽ���P2P�������������̷�������Ϣ
	void EnrolUsr(CString strMsgData);                               //�Ǽ�ע���û�
	void UpdUsr(CString strMsgData);                                 //�����û��б�
	void PtoPsrvProvdr(CString strMsgData);                          //�ṩP2P��ַ����
	void SendMsgtoPer(CString strMsgData);                           //��Է�����������Ϣ
	void ShowMsgfrmPer(CString strMsgData);                          //��ʾ�Է���������������
	void StartSndSocket(CString msgtoSnd,CString sIP,CString sPort); //��ʱ����һ��ר���ڷ�����Ϣ���׽���
public:
	SOCKET SelfSndSocket;                                            //�����������ڷ�����Ϣ��SOCKET
	SOCKET SelfRcvSocket;                                            //�����������ڽ�����Ϣ��SOCKET
	SOCKADDR_IN m_sockSelfSndAddr;                                   //SOCKET �ṹ,���ͽ��̵�Ĭ�ϵ�ַ��127.0.0.1:8888��
    SOCKADDR_IN m_sockSelfRcvAddr;                                   //SOCKET �ṹ,���ս��̵ĵ�ַ��������ʶ������ϵͳ��
	SOCKADDR_IN m_sockAddrto;                                        //SOCKET �ṹ,ָ����Ҫ���ĸ���ַ����Ϣ
	RgstdUsr rstUsr[100];
	int rstUsrCont;                                                  //ע���û���
	int onlUsrCont;                                                  //�����û���
	Msg msgbuf;
	CString RegisterAddr;                                            //ע������Ϣ
	CString OnlUsrInfo;                                              //���߸�������Ϣ
	CString PtoPsrvReqst;                                            //������������Ϣ
	CString PtoPsrvRspse;                                            //������Ӧ����Ϣ
	CString MsgTalktoPeer;                                           //������Ϣ����Ϣ
	int socklen;
//ADD
	CIPAddressCtrl SevrIP;
	CString sevrPort;
	CIPAddressCtrl LocaIP;
	CString locaPort;
	CString nickname;
	CEdit m_MessageList;
	CListBox m_UserList;
	CString strMessage;
protected:
	virtual void OnOK();
public:
	afx_msg void OnStop();
	afx_msg void OnLogin();
	afx_msg void OnLogout();
	afx_msg void OnSend();
	CEdit m_EditWords;
	CButton m_Start;
	CButton m_Stop;
	CEdit m_LcaPrt;
	CButton m_Login;
	CButton m_Logout;
	CEdit m_SvrPrt;
	CEdit m_nicnam;
	CButton m_Send;
	CButton m_exit;
	afx_msg void OnBnClickedButton4();
};
