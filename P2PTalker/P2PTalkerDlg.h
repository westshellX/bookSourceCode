// P2PTalkerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//ADD
#include "rgstdUsr.h"
#include "stdafx.h"
#include "MyMsg.h"
//ADD


// CP2PTalkerDlg 对话框
class CP2PTalkerDlg : public CDialog
{
// 构造
public:
	CP2PTalkerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_P2PTALKER_DIALOG };

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

//ADD
	LRESULT OnReadMsg(WPARAM wParam,LPARAM lParam);                  //用于接收P2P网络中其他进程发来的消息
	void EnrolUsr(CString strMsgData);                               //登记注册用户
	void UpdUsr(CString strMsgData);                                 //更新用户列表
	void PtoPsrvProvdr(CString strMsgData);                          //提供P2P地址服务
	void SendMsgtoPer(CString strMsgData);                           //向对方发送聊天信息
	void ShowMsgfrmPer(CString strMsgData);                          //显示对方发来的聊天内容
	void StartSndSocket(CString msgtoSnd,CString sIP,CString sPort); //临时开启一个专用于发送消息的套接字
public:
	SOCKET SelfSndSocket;                                            //本机进程用于发送消息的SOCKET
	SOCKET SelfRcvSocket;                                            //本机进程用于接收消息的SOCKET
	SOCKADDR_IN m_sockSelfSndAddr;                                   //SOCKET 结构,发送进程的默认地址（127.0.0.1:8888）
    SOCKADDR_IN m_sockSelfRcvAddr;                                   //SOCKET 结构,接收进程的地址（用来标识各个端系统）
	SOCKADDR_IN m_sockAddrto;                                        //SOCKET 结构,指定将要向哪个地址发消息
	RgstdUsr rstUsr[100];
	int rstUsrCont;                                                  //注册用户数
	int onlUsrCont;                                                  //在线用户数
	Msg msgbuf;
	CString RegisterAddr;                                            //注册类消息
	CString OnlUsrInfo;                                              //在线更新类消息
	CString PtoPsrvReqst;                                            //服务请求类消息
	CString PtoPsrvRspse;                                            //服务响应类消息
	CString MsgTalktoPeer;                                           //聊天信息类消息
	int socklen;
//ADD
	CIPAddressCtrl SevrIP;
	CString sevrPort;
	CIPAddressCtrl LocaIP;
	CString locaPort;
	CString nickname;
	CEdit m_MessageList;
	CListBox m_UserList;
	CString strMessage;
protected:
	virtual void OnOK();
public:
	afx_msg void OnStop();
	afx_msg void OnLogin();
	afx_msg void OnLogout();
	afx_msg void OnSend();
	CEdit m_EditWords;
	CButton m_Start;
	CButton m_Stop;
	CEdit m_LcaPrt;
	CButton m_Login;
	CButton m_Logout;
	CEdit m_SvrPrt;
	CEdit m_nicnam;
	CButton m_Send;
	CButton m_exit;
	afx_msg void OnBnClickedButton4();
};
