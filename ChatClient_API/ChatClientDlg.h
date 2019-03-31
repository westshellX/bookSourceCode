// ChatClientDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CChatClientDlg 对话框
class CChatClientDlg : public CDialog
{
// 构造
public:
//ADD
	void ReceiveData();
	void CloseSock();
//ADD
	CChatClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHATCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
//ADD
public:
	SOCKET m_client;                    //SOCKET
//ADD


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
