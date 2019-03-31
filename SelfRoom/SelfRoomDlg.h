// SelfRoomDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

//ADD
class CServerSocket;
class CClientSocket;
//ADD
// CSelfRoomDlg �Ի���
class CSelfRoomDlg : public CDialog
{
// ����
public:
	CSelfRoomDlg(CWnd* pParent = NULL);	// ��׼���캯��
//ADD
	CServerSocket *m_pSocket;
	CClientSocket *clientSocket;
	void UpdateUser(CClientSocket *pSocket);
//ADD

// �Ի�������
	enum { IDD = IDD_SELFROOM_DIALOG };

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
	CString m_strName;
	CListBox m_UserList;
	CIPAddressCtrl ServerIP;
	CEdit ServerPort;
	CString sPort;
	CString m_history;
	afx_msg void OnStart();
	CEdit m_MessageList;
	afx_msg void OnStop();
	CEdit m_Admin;
	CButton m_Start;
	CButton m_Stop;
	CButton m_Exit;
	afx_msg void OnBnClickedButton3();
};
