// UDProcsCommDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CUDProcsCommDlg �Ի���
class CUDProcsCommDlg : public CDialog
{
// ����
public:
	CUDProcsCommDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UDPROCSCOMM_DIALOG };
//ADD
	UINT	m_sport;
	UINT	m_dport;
//ADD

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
//ADD
	LRESULT OnReadClose(WPARAM wParam,LPARAM lParam);
	public:

	SOCKET Client;                          //�ͻ�����������
	SOCKET ServerSocket;                    //SOCKET 
	SOCKADDR_IN m_sockServerAddr;           //SOCKET �ṹ
	SOCKADDR_IN m_sockAddrto;               //SOCKET �ṹ

	int socklen;

	BOOL IsTrue;

	Msg msg;
//ADD


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
