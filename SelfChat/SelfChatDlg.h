// SelfChatDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//ADD
#include "ClientSocket.h"
//ADD


// CSelfChatDlg 对话框
class CSelfChatDlg : public CDialog
{
// 构造
public:
//ADD
	CClientSocket *m_pSocket;
	void UpdateUser();
	BOOL GetMsgFromRoom();
//ADD
	CSelfChatDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SELFCHAT_DIALOG };

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
	CIPAddressCtrl ServerIP;
	CListBox m_UserList;
	CEdit m_MessageList;
	CString m_strMessage;
	afx_msg void OnEnter();
	CEdit m_port;
	CString strport;
	afx_msg void OnQuit();
	afx_msg void OnSend();
	CEdit m_EditWords;
	CEdit m_Usr;
	CButton m_Enter;
	CButton m_Quit;
	CButton m_Send;
	CButton m_Refresh;
	CButton m_Exit;
	afx_msg void OnRefresh();
	afx_msg void OnBnClickedButton5();
};
