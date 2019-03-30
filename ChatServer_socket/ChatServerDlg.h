// ChatServerDlg.h : ͷ�ļ�
//

#pragma once
//ADD
#include "MySocket.h"
#include "afxcmn.h"
#include "afxwin.h"
//ADD

// CChatServerDlg �Ի���
class CChatServerDlg : public CDialog
{
// ����
public:
//ADD
	MySocket * m_ServerSocket;
	MySocket * m_ListenSocket;
	CArchive * m_archiveIn;
	CArchive * m_archiveOut;
	CSocketFile * m_socketfile;
	void OnAccept();
	void OnReceive();
	void OnClose();
	void SocketReset();
//ADD
	CChatServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATSERVER_DIALOG };

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
public:
	CIPAddressCtrl ServerIP;
	CEdit ServerPort;
	int sPort;
	CEdit m_EditWords;
	CString m_sWords;
	CListBox m_ListWords;
//ADD
	CString m_Input;
//ADD
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CButton m_ButtonDisconnect;
	CButton m_ButtonClear;
	CButton m_ButtonExit;
	CButton m_ButtonListen;
	CButton m_ButtonStopListen;
	CButton m_ButtonSend;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
