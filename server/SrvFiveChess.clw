; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRightPanel
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "srvfivechess.h"
LastPage=0

ClassCount=10
Class1=CBlackStatic
Class2=CChessBorad
Class3=CClientSock
Class4=CLeftPanel
Class5=CRightPanel
Class6=CServerSetting
Class7=CSrvFiveChessApp
Class8=CAboutDlg
Class9=CSrvFiveChessDlg
Class10=CSrvSock

ResourceCount=7
Resource1=IDD_RIGHTPANEL_DIALOG
Resource2=IDD_SERVERSETTING_DIALOG
Resource3=IDD_SRVFIVECHESS_DIALOG
Resource4=IDD_CHESSBORAD_DIALOG
Resource5=IDD_LEFTPANEL_DIALOG
Resource6=IDD_ABOUTBOX
Resource7=IDR_MAINMENU

[CLS:CBlackStatic]
Type=0
BaseClass=CStatic
HeaderFile=BlackStatic.h
ImplementationFile=BlackStatic.cpp
Filter=W
VirtualFilter=WC

[CLS:CChessBorad]
Type=0
BaseClass=CDialog
HeaderFile=ChessBorad.h
ImplementationFile=ChessBorad.cpp
Filter=D
VirtualFilter=dWC

[CLS:CClientSock]
Type=0
BaseClass=CSocket
HeaderFile=ClientSock.h
ImplementationFile=ClientSock.cpp

[CLS:CLeftPanel]
Type=0
BaseClass=CDialog
HeaderFile=LeftPanel.h
ImplementationFile=LeftPanel.cpp
Filter=D
VirtualFilter=dWC

[CLS:CRightPanel]
Type=0
BaseClass=CDialog
HeaderFile=RightPanel.h
ImplementationFile=RightPanel.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_SENDMSG

[CLS:CServerSetting]
Type=0
BaseClass=CDialog
HeaderFile=ServerSetting.h
ImplementationFile=ServerSetting.cpp
Filter=D
VirtualFilter=dWC

[CLS:CSrvFiveChessApp]
Type=0
BaseClass=CWinApp
HeaderFile=SrvFiveChess.h
ImplementationFile=SrvFiveChess.cpp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SrvFiveChessDlg.h
ImplementationFile=SrvFiveChessDlg.cpp
LastObject=CAboutDlg

[CLS:CSrvFiveChessDlg]
Type=0
BaseClass=CDialog
HeaderFile=SrvFiveChessDlg.h
ImplementationFile=SrvFiveChessDlg.cpp
Filter=W
VirtualFilter=dWC

[CLS:CSrvSock]
Type=0
BaseClass=CSocket
HeaderFile=SrvSock.h
ImplementationFile=SrvSock.cpp

[DLG:IDD_CHESSBORAD_DIALOG]
Type=1
Class=CChessBorad
ControlCount=0

[DLG:IDD_LEFTPANEL_DIALOG]
Type=1
Class=CLeftPanel
ControlCount=6
Control1=IDC_STATIC,static,1342177294
Control2=IDC_BT_BACK,button,1342242816
Control3=IDC_DRAW_CHESS,button,1342242816
Control4=IDC_BEGINGAME,button,1342242816
Control5=IDC_GIVE_UP,button,1342242816
Control6=IDC_BACK_PLAY,button,1342242816

[DLG:IDD_RIGHTPANEL_DIALOG]
Type=1
Class=CRightPanel
ControlCount=14
Control1=IDC_STATIC,static,1342177294
Control2=IDC_USERLIST,SysListView32,1350631425
Control3=IDC_CONVERSATION,RICHEDIT,1342244996
Control4=IDC_SENDMSG,button,1342242816
Control5=IDC_PANEL1,static,1342177287
Control6=IDC_PANEL2,static,1342177287
Control7=IDC_PANEL3,static,1342177287
Control8=IDC_STATIC,static,1342177294
Control9=IDC_USER,static,1342308364
Control10=IDC_NETSTATE,static,1342308352
Control11=IDC_MESSAGE,RICHEDIT,1342242944
Control12=IDC_TOP,static,1342308352
Control13=IDC_BOTTOM,static,1342308352
Control14=IDC_FRAME1,static,1342308352

[DLG:IDD_SERVERSETTING_DIALOG]
Type=1
Class=CServerSetting
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_HOSTNAME,edit,1350633600
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PORT,edit,1350639744
Control6=IDC_SET,button,1342242816
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_NICKNAME,edit,1350631552

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SRVFIVECHESS_DIALOG]
Type=1
Class=CSrvFiveChessDlg
ControlCount=0

[MNU:IDR_MAINMENU]
Type=1
Class=?
Command1=ID_MENUSVRSETTING
Command2=ID_MENUIDM_ABOUTBOX
CommandCount=2

