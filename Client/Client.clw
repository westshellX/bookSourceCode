; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=login
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Client.h"

ClassCount=5
Class1=CClientApp
Class2=CClientDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_CLIENT_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=login
Class5=CMysocket
Resource4=IDD_LOGIN_DIALOG

[CLS:CClientApp]
Type=0
HeaderFile=Client.h
ImplementationFile=Client.cpp
Filter=N

[CLS:CClientDlg]
Type=0
HeaderFile=ClientDlg.h
ImplementationFile=ClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CClientDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ClientDlg.h
ImplementationFile=ClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CLIENT_DIALOG]
Type=1
Class=CClientDlg
ControlCount=4
Control1=IDOK,button,1342242816
Control2=IDC_LIST1,listbox,1352728835
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631556

[DLG:IDD_LOGIN_DIALOG]
Type=1
Class=login
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_EDIT3,edit,1350631552

[CLS:login]
Type=0
HeaderFile=login.h
ImplementationFile=login.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CMysocket]
Type=0
HeaderFile=Mysocket.h
ImplementationFile=Mysocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

