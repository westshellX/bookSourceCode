// ChatServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//ADD
#include "ListenSocket.h"
#include "ServerSocket.h"
//ADD


// CChatServerDlg �Ի���
class CChatServerDlg : public CDialog
{
// ����
public:
//ADD
	CServerSocket m_ServerSocket;
	CListenSocket m_ListenSocket;
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
	CListBox m_ListWords;
	CButton m_ButtonClear;
	CButton m_ButtonExit;
	CButton m_ButtonListen;
	CButton m_ButtonStopListen;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CButton m_ButtonDisconnect;
	CEdit m_EditWords;
	CString m_sWords;
	CButton m_ButtonSend;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
