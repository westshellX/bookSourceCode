// ChatClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CChatClientDlg �Ի���
class CChatClientDlg : public CDialog
{
// ����
public:
//ADD
	void ReceiveData();
	void CloseSock();
//ADD
	CChatClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
//ADD
public:
	SOCKET m_client;                    //SOCKET
//ADD


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
	afx_msg void OnConnect();
	CIPAddressCtrl ServerIP;
	CEdit ServerPort;
	CString sPort;
	CListBox m_ListWords;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSend();
	CEdit m_EditWords;
	CString m_sWords;
	CButton m_ButtonConnect;
	CButton m_ButtonDisconnect;
	CButton m_ButtonClear;
	CButton m_ButtonSend;
	CButton m_ButtonExit;
	afx_msg void OnDisconnect();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton1();
};
