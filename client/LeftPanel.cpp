// LeftPanel.cpp : implementation file
//

#include "stdafx.h"
#include "clientfivechess.h"
#include "LeftPanel.h"
#include "ClientFiveChessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftPanel dialog


CLeftPanel::CLeftPanel(CWnd* pParent /*=NULL*/)
	: CDialog(CLeftPanel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLeftPanel)
	//}}AFX_DATA_INIT
}


void CLeftPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLeftPanel)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLeftPanel, CDialog)
	//{{AFX_MSG_MAP(CLeftPanel)
	ON_BN_CLICKED(IDC_BEGINGAME, OnBegingame)
	ON_BN_CLICKED(IDC_BT_BACK, OnBtBack)
	ON_BN_CLICKED(IDC_DRAW_CHESS, OnDrawChess)
	ON_BN_CLICKED(IDC_GIVE_UP, OnGiveUp)
	ON_BN_CLICKED(IDC_BACK_PLAY, OnBackPlay)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftPanel message handlers

void CLeftPanel::OnOK() 
{

}

void CLeftPanel::OnCancel() 
{


}

void CLeftPanel::OnBegingame() 
{
	CClientFiveChessDlg * pDlg = (CClientFiveChessDlg*)GetParent();
	pDlg->OnBegin();
}

void CLeftPanel::OnBtBack() 
{
	//判断游戏是否进行中
	CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
	if (pDlg->m_ChessBoard.m_State==esBEGIN)
	{
		//发出悔棋请求
		TCP_PACKAGE tcpPackage;
		tcpPackage.cmdType = CT_BACKREQUEST;
		//用户已经下棋
		if (pDlg->m_ChessBoard.m_LocalChessPT.x > -1  //chessboard对象刚创建时，m_LocalChessPT.x 的值为-1
			&& pDlg->m_ChessBoard.m_LocalChessPT.y > -1 )	
		{
			pDlg->m_ChessBoard.m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));
		}
		else  //游戏刚开始的时候，用户还没有下棋，则拒绝悔棋
		{
			MessageBox("当前不允许悔棋!","提示");
		}
	}	
}

//和棋
void CLeftPanel::OnDrawChess() 
{
	//判断游戏是否进行中
	CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
	if (pDlg->m_ChessBoard.m_State==esBEGIN)
	{
		//发送和棋请求
		TCP_PACKAGE tcpPackage;
		tcpPackage.cmdType = CT_DRAWCHESSREQUEST;
		pDlg->m_ChessBoard.m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));
	}

	
}

void CLeftPanel::OnGiveUp() 
{
	//判断游戏是否进行中
	CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
	if (pDlg->m_ChessBoard.m_State==esBEGIN)
	{
		if (MessageBox("确实要认输吗?","提示",MB_YESNO)==IDYES)
		{
			//发送认输信息
			TCP_PACKAGE tcpPackage;
			tcpPackage.cmdType = CT_GIVEUP;
			pDlg->m_ChessBoard.m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));

			//进行游戏结束处理
			//进行和棋处理，游戏结束
			pDlg->m_ChessBoard.m_TestNum = 0;

			pDlg->m_ChessBoard.m_IsDown = FALSE;
			pDlg->m_ChessBoard.m_IsStart = FALSE;
			pDlg->m_ChessBoard.m_IsWin = FALSE;
			pDlg->m_ChessBoard.m_State = esEND;
			pDlg->m_ChessBoard.InitializeNode();
			//更新界面
			pDlg->m_ChessBoard.Invalidate();
			pDlg->m_ChessBoard.m_LocalChessPT.x = pDlg->m_ChessBoard.m_LocalChessPT.y = -1;
			pDlg->m_ChessBoard.m_RemoteChessPT.x = pDlg->m_ChessBoard.m_RemoteChessPT.y  = -1;
			MessageBox("您输了!","提示");
		}
	}	
}


void CLeftPanel::OnBackPlay() 
{
	//游戏进行中不允许回放
	CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
	if (pDlg->m_ChessBoard.m_State==esEND)
	{
		if (pDlg->m_ChessBoard.m_BackPlayList.GetCount()>0)
		{
			
			
			//首先清空棋盘
			pDlg->m_ChessBoard.InitializeNode();
			pDlg->m_ChessBoard.Invalidate();
			
			//进行游戏回放

			pDlg->m_ChessBoard.GamePlayBack();
		
		}
		else
		{
			MessageBox("当前没有游戏记录!","提示");
		
		}
	
	}
	else
	{
		MessageBox("当前不允许回放!","提示");
	}	
}

void CLeftPanel::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBrush brush(RGB(247,227,199));


	CDC* pwndDC = GetDC();
	CRect rc;
	GetClientRect(rc);
	pwndDC->FillRect(rc,&brush);	
	// Do not call CDialog::OnPaint() for painting messages
}
