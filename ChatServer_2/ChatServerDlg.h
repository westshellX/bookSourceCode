// ChatServerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//ADD
#include "MySocket.h"
//ADD

// CChatServerDlg 对话框
class CChatServerDlg : public CDialog
{
// 构造
public:
//ADD
	MySocket * m_ServerSocket;
    MySocket * m_ListenSocket;
	void OnReceive();
	void OnClose();
	void OnAccept();
	void SocketReset();
//ADD
	CChatServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHATSERVER_DIALOG };

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
	CListBox m_ListWords;
	CButton m_ButtonDisconnect;
	CButton m_ButtonClear;
	CButton m_ButtonExit;
	CButton m_ButtonListen;
	CButton m_ButtonStopListen;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1();
	CString m_sWords;
	CEdit m_EditWords;
	CButton m_ButtonSend;
	afx_msg void OnBnClickedCancel();
};
