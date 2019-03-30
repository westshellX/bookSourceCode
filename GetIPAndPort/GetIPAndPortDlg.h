// GetIPAndPortDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CGetIPAndPortDlg 对话框
class CGetIPAndPortDlg : public CDialog
{
// 构造
public:
	CGetIPAndPortDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GETIPANDPORT_DIALOG };

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
	CIPAddressCtrl m_ip;
	CEdit m_port;
	CEdit m_showIpAndPort;
	afx_msg void OnShowIpAndPort();
	CString strport;
	afx_msg void OnBnClickedButton2();
};
