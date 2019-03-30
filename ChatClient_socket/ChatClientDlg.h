// ChatClientDlg.h : ͷ�ļ�
//

#pragma once
//ADD
#include "MySocket.h"
#include "afxcmn.h"
#include "afxwin.h"
//ADD

// CChatClientDlg �Ի���
class CChatClientDlg : public CDialog
{
// ����
public:
//ADD
	MySocket * m_ClientSocket;
	CArchive * m_archiveIn;
	CArchive * m_archiveOut;
	CSocketFile * m_socketfile;
	void OnReceive();
	void OnClose();
	void SocketReset();
//ADD
	CChatClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATCLIENT_DIALOG };

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
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CButton m_ButtonConnect;
	CButton m_ButtonDisconnect;
	CButton m_ButtonClear;
	CButton m_ButtonSend;
	CButton m_ButtonExit;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
