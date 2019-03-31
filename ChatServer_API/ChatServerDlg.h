// ChatServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CChatServerDlg �Ի���
class CChatServerDlg : public CDialog
{
// ����
public:
//ADD
	void HandleData();
	void ReceiveData();
	void CloseSock();
//ADD
	CChatServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
//ADD
	SOCKET m_server,m_client;
//ADD

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
	afx_msg void OnListen();
	CIPAddressCtrl ServerIP;
	CEdit ServerPort;
	CString sPort;
	CListBox m_ListWords;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_EditWords;
	CString m_sWords;
	afx_msg void OnSend();
	CButton m_ButtonListen;
	CButton m_ButtonStopListen;
	CButton m_ButtonDisconnect;
	CButton m_ButtonClear;
	CButton m_ButtonSend;
	CButton m_ButtonExit;
	afx_msg void OnStopListen();
	afx_msg void OnDisconnect();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton1();
};
