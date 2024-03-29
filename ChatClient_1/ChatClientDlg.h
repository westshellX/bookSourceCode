// ChatClientDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//ADD
#include "ClientSocket.h"
//ADD

// CChatClientDlg 对话框
class CChatClientDlg : public CDialog
{
// 构造
public:
//ADD
	CClientSocket m_ClientSocket;
//ADD
	CChatClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHATCLIENT_DIALOG };

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
	CIPAddressCtrl ServerIP;
	CEdit ServerPort;
	int sPort;
	CButton m_ButtonConnect;
	CButton m_ButtonDisconnect;
	CListBox m_ListWords;
	CButton m_ButtonClear;
	CEdit m_EditWords;
	CString m_sWords;
	CButton m_ButtonSend;
	CButton m_ButtonExit;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton1();
};
