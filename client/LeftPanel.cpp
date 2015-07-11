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
	//�ж���Ϸ�Ƿ������
	CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
	if (pDlg->m_ChessBoard.m_State==esBEGIN)
	{
		//������������
		TCP_PACKAGE tcpPackage;
		tcpPackage.cmdType = CT_BACKREQUEST;
		//�û��Ѿ�����
		if (pDlg->m_ChessBoard.m_LocalChessPT.x > -1  //chessboard����մ���ʱ��m_LocalChessPT.x ��ֵΪ-1
			&& pDlg->m_ChessBoard.m_LocalChessPT.y > -1 )	
		{
			pDlg->m_ChessBoard.m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));
		}
		else  //��Ϸ�տ�ʼ��ʱ���û���û�����壬��ܾ�����
		{
			MessageBox("��ǰ���������!","��ʾ");
		}
	}	
}

//����
void CLeftPanel::OnDrawChess() 
{
	//�ж���Ϸ�Ƿ������
	CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
	if (pDlg->m_ChessBoard.m_State==esBEGIN)
	{
		//���ͺ�������
		TCP_PACKAGE tcpPackage;
		tcpPackage.cmdType = CT_DRAWCHESSREQUEST;
		pDlg->m_ChessBoard.m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));
	}

	
}

void CLeftPanel::OnGiveUp() 
{
	//�ж���Ϸ�Ƿ������
	CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
	if (pDlg->m_ChessBoard.m_State==esBEGIN)
	{
		if (MessageBox("ȷʵҪ������?","��ʾ",MB_YESNO)==IDYES)
		{
			//����������Ϣ
			TCP_PACKAGE tcpPackage;
			tcpPackage.cmdType = CT_GIVEUP;
			pDlg->m_ChessBoard.m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));

			//������Ϸ��������
			//���к��崦����Ϸ����
			pDlg->m_ChessBoard.m_TestNum = 0;

			pDlg->m_ChessBoard.m_IsDown = FALSE;
			pDlg->m_ChessBoard.m_IsStart = FALSE;
			pDlg->m_ChessBoard.m_IsWin = FALSE;
			pDlg->m_ChessBoard.m_State = esEND;
			pDlg->m_ChessBoard.InitializeNode();
			//���½���
			pDlg->m_ChessBoard.Invalidate();
			pDlg->m_ChessBoard.m_LocalChessPT.x = pDlg->m_ChessBoard.m_LocalChessPT.y = -1;
			pDlg->m_ChessBoard.m_RemoteChessPT.x = pDlg->m_ChessBoard.m_RemoteChessPT.y  = -1;
			MessageBox("������!","��ʾ");
		}
	}	
}


void CLeftPanel::OnBackPlay() 
{
	//��Ϸ�����в�����ط�
	CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
	if (pDlg->m_ChessBoard.m_State==esEND)
	{
		if (pDlg->m_ChessBoard.m_BackPlayList.GetCount()>0)
		{
			
			
			//�����������
			pDlg->m_ChessBoard.InitializeNode();
			pDlg->m_ChessBoard.Invalidate();
			
			//������Ϸ�ط�

			pDlg->m_ChessBoard.GamePlayBack();
		
		}
		else
		{
			MessageBox("��ǰû����Ϸ��¼!","��ʾ");
		
		}
	
	}
	else
	{
		MessageBox("��ǰ������ط�!","��ʾ");
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
