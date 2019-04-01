
// HelloMFCDlg.h : 头文件
//

#pragma once

#include "scjNet.h"
#include "afxcmn.h"
#include "afxwin.h"

// CHelloMFCDlg 对话框
class CHelloMFCDlg : public CDialogEx
{
// 构造
public:
	CHelloMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	LRESULT  scjNetRecv(WPARAM wp,LPARAM lp);

public:
	scjNet* pNet;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnBnClickedButtonConnect();
	// 服务器IP地址控件
	CIPAddressCtrl ServerIP;
	CEdit ServerPort;
	int sPort;
};
