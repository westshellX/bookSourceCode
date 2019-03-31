// UDProcsCommDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CUDProcsCommDlg 对话框
class CUDProcsCommDlg : public CDialog
{
// 构造
public:
	CUDProcsCommDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UDPROCSCOMM_DIALOG };
//ADD
	UINT	m_sport;
	UINT	m_dport;
//ADD

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
//ADD
	LRESULT OnReadClose(WPARAM wParam,LPARAM lParam);
	public:

	SOCKET Client;                          //客户的连接请求
	SOCKET ServerSocket;                    //SOCKET 
	SOCKADDR_IN m_sockServerAddr;           //SOCKET 结构
	SOCKADDR_IN m_sockAddrto;               //SOCKET 结构

	int socklen;

	BOOL IsTrue;

	Msg msg;
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
	CListBox list;
	CString str;
	CIPAddressCtrl IPLocal;
	CString LocalPort;
	CIPAddressCtrl IPDest;
	CString DestPort;
protected:
	virtual void OnOK();
public:
	afx_msg void OnStop();
	afx_msg void OnSend();
	CEdit PortLocal;
	CEdit PortDest;
	CEdit m_EditWords;
	CButton m_Start;
	CButton m_Stop;
	CButton m_Send;
	CButton m_Exit;
	afx_msg void OnBnClickedButton2();
};
