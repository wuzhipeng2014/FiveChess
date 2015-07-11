// RightPanel.cpp : implementation file
//

#include "stdafx.h"
#include "ClientFiveChess.h"
#include "RightPanel.h"
#include "ClientFiveChessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRightPanel dialog


CRightPanel::CRightPanel(CWnd* pParent /*=NULL*/)
	: CDialog(CRightPanel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRightPanel)
	//}}AFX_DATA_INIT
	m_TextFont.CreateFont(16,0,0,0,600,0,0,0,DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 						      
							CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,"宋体");

	m_SendTextFont.CreateFont(16,0,0,0,600,0,0,0,DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 						      
							CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,"宋体");
	m_NetState.m_bDrawFrame = FALSE;	//取消边框
	m_User.m_bDrawFrame = FALSE;		//取消边框
	m_Top.m_bDrawFrame = FALSE;
	m_Bottom.m_bDrawFrame = FALSE;
	m_Initialized = FALSE;

}


void CRightPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRightPanel)
	DDX_Control(pDX, IDC_SENDMSG, m_SendBtn);
	DDX_Control(pDX, IDC_BOTTOM, m_Bottom);
	DDX_Control(pDX, IDC_TOP, m_Top);
	DDX_Control(pDX, IDC_NETSTATE2, m_Frame1);
	DDX_Control(pDX, IDC_MESSAGE, m_Msg);
	DDX_Control(pDX, IDC_USER, m_User);
	DDX_Control(pDX, IDC_NETSTATE, m_NetState);
	DDX_Control(pDX, IDC_CONVERSATION, m_MsgList);
	DDX_Control(pDX, IDC_USERLIST, m_UserList);
	DDX_Control(pDX, IDC_PANEL3, m_Panel3);
	DDX_Control(pDX, IDC_PANEL2, m_Panel2);
	DDX_Control(pDX, IDC_PANEL1, m_Panel1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRightPanel, CDialog)
	//{{AFX_MSG_MAP(CRightPanel)
	ON_BN_CLICKED(IDC_SENDMSG, OnSendMsg)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRightPanel message handlers

void CRightPanel::OnOK()
{

}

void CRightPanel::OnCancel()
{

}

BOOL CRightPanel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_UserList.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT | LVS_EX_TWOCLICKACTIVATE );
	m_UserList.InsertColumn(0,"昵称",LVCFMT_LEFT,65);
	m_UserList.InsertColumn(1,"主机信息",LVCFMT_LEFT,85);
	m_UserList.InsertColumn(2,"联机时间",LVCFMT_LEFT,80);

	m_User.SetFont(&m_TextFont);
	m_Msg.SetFont(&m_SendTextFont);

	m_NetState.SetWindowText("网路状态:未连接");

	m_UserList.SetBkColor(RGB(247,227,199));
	m_MsgList.SetBackgroundColor(FALSE,RGB(247,227,199));
	m_Msg.SetBackgroundColor(FALSE,RGB(247,227,199));
	m_UserList.SetTextBkColor(RGB(247,227,199));

	CRect editRC,cltRC,panelRC;
	m_Frame1.GetClientRect(editRC);
	m_Frame1.MapWindowPoints(this,editRC);
	GetClientRect(cltRC);

	m_nEditToBottom = cltRC.Height()-editRC.bottom;
	
	m_Panel3.GetClientRect(panelRC);
	m_Panel3.MapWindowPoints(this,panelRC);
	m_nPanelToBottom = cltRC.Height()- panelRC.bottom;

	m_Initialized = TRUE;


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRightPanel::OnSendMsg() 
{
	//判断是否处于连接状态
	CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
	if (pDlg->m_ChessBoard.m_IsConnect)
	{
		CString csText;
		m_Msg.GetWindowText(csText);
		if (!csText.IsEmpty() && csText.GetLength()< 512)
		{
			TCP_PACKAGE txtPackage;
			memset(&txtPackage,0,sizeof(TCP_PACKAGE));
			txtPackage.cmdType = CT_TEXT;
			strcpy(txtPackage.chText,csText);
			pDlg->m_ChessBoard.m_ClientSock.Send(&txtPackage,sizeof(TCP_PACKAGE));

			CString csNickName = m_UserList.GetItemText(0,0);	//获取用户昵称
			csNickName += "说:";
			csText = csNickName + csText;
			m_MsgList.SetSel(-1,-1);
			m_MsgList.ReplaceSel(csText);
	
			m_MsgList.SetSel(-1,-1);
			m_MsgList.ReplaceSel("\n");
			m_Msg.SetWindowText("");
		}
	}
}




void CRightPanel::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_Initialized == TRUE)
	{
		CRect editRC,cltRC,panelRC;	
		GetClientRect(cltRC);

		m_Panel3.GetClientRect(panelRC);
		m_Panel3.MapWindowPoints(this,panelRC);
		m_Frame1.GetClientRect(editRC);
		m_Frame1.MapWindowPoints(this,editRC);
		
		int nPanelBottom = cltRC.Height()-m_nPanelToBottom;

		panelRC.bottom = nPanelBottom;
		m_Panel3.MoveWindow(panelRC);
		panelRC.DeflateRect(1,1,1,1);
		m_MsgList.MoveWindow(panelRC);

		int nEditBottom = cltRC.Height()-m_nEditToBottom;
		int nEditHeight = editRC.Height();

		editRC.bottom = nEditBottom ;
		editRC.top = nEditBottom-nEditHeight;
		m_Frame1.MoveWindow(editRC);
		editRC.DeflateRect(1,1,1,1);
		m_Msg.MoveWindow(editRC);
		
		CRect ButtonRC;
		m_SendBtn.GetClientRect(ButtonRC);
		


		editRC.OffsetRect(editRC.Width()+10,0);
		editRC.right = editRC.left + ButtonRC.Width();
		m_SendBtn.MoveWindow(editRC);
		GetParent()->Invalidate();
	}	
}

void CRightPanel::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBrush brush(RGB(247,227,199));


	CDC* pwndDC = GetDC();
	CRect rc;
	GetClientRect(rc);
	pwndDC->FillRect(rc,&brush);	
	// Do not call CDialog::OnPaint() for painting messages
}
