// GetIPAndPortDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CGetIPAndPortDlg �Ի���
class CGetIPAndPortDlg : public CDialog
{
// ����
public:
	CGetIPAndPortDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GETIPANDPORT_DIALOG };

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
	CIPAddressCtrl m_ip;
	CEdit m_port;
	CEdit m_showIpAndPort;
	afx_msg void OnShowIpAndPort();
	CString strport;
	afx_msg void OnBnClickedButton2();
};
