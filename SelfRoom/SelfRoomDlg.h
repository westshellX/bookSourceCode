// SelfRoomDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

//ADD
class CServerSocket;
class CClientSocket;
//ADD
// CSelfRoomDlg 对话框
class CSelfRoomDlg : public CDialog
{
// 构造
public:
	CSelfRoomDlg(CWnd* pParent = NULL);	// 标准构造函数
//ADD
	CServerSocket *m_pSocket;
	CClientSocket *clientSocket;
	void UpdateUser(CClientSocket *pSocket);
//ADD

// 对话框数据
	enum { IDD = IDD_SELFROOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
