
// HelloMFCDlg.h : ͷ�ļ�
//

#pragma once

#include "scjNet.h"
#include "afxcmn.h"
#include "afxwin.h"

// CHelloMFCDlg �Ի���
class CHelloMFCDlg : public CDialogEx
{
// ����
public:
	CHelloMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	LRESULT  scjNetRecv(WPARAM wp,LPARAM lp);

public:
	scjNet* pNet;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnBnClickedButtonConnect();
	// ������IP��ַ�ؼ�
	CIPAddressCtrl ServerIP;
	CEdit ServerPort;
	int sPort;
};
